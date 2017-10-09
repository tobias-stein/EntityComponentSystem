///-------------------------------------------------------------------------------------------------
/// File:	RenderSystem.cpp.
///
/// Summary:	Implements the render system class.
///-------------------------------------------------------------------------------------------------

#include "RenderSystem.h"

RenderSystem::RenderSystem(SDL_Window* window) :
	m_Window(window),
	m_BufferedShapes(IShape::MAX_SHAPES, nullptr)
{
	InitializeOpenGL();

	// create global vertex and index buffer
	this->m_VertexBuffer = new VertexBuffer(GLOBAL_VERTEX_BUFFER_SIZE);
	this->m_IndexBuffer = new IndexBuffer(GLOBAL_INDEX_BUFFER_SIZE);

	RegisterEventCallbacks();
}

RenderSystem::~RenderSystem()
{
	UnregisterEventCallbacks();

	for (size_t i = 0; i < this->m_BufferedShapes.size(); ++i)
	{
		delete this->m_BufferedShapes[i];
		this->m_BufferedShapes[i] = nullptr;
	}
	this->m_BufferedShapes.clear();

	for (auto it : this->m_RenderableGroups)
	{		
		it.first.Delete();
		it.second.clear();
	}
	
	
	// free global vertex and index buffer
	this->m_VertexBuffer = nullptr;
	delete this->m_VertexBuffer;

	this->m_IndexBuffer = nullptr;
	delete this->m_IndexBuffer;

	TerminateOpenGL();
}


void RenderSystem::InitializeOpenGL()
{
	this->m_Context = SDL_GL_CreateContext(this->m_Window);
	assert(this->m_Context != 0 && "Failed to create OpenGL context!");


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// OpenGL verison 4.5 (released 2014)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Use Vsync
	SDL_GL_SetSwapInterval(1);


	// init glew 
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	assert(glewError == GLEW_OK  && glewGetErrorString(glewError));


	// Clear framebuffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// Check for errors.
	glGetLastError();
}

void RenderSystem::TerminateOpenGL()
{
	// Destroy OpenGL context
	if (this->m_Context)
		SDL_GL_DeleteContext(this->m_Context);
}

void RenderSystem::PreUpdate(float dt)
{
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Update(float dt)
{
	MaterialID		lastUsedMaterial	= INVALID_MATERIAL_ID;
	VertexArrayID	lastUsedVertexArray = -1;

	for (auto renderableGroup : this->m_RenderableGroups)
	{
		// activate vertex array, if different from current bound
		if (renderableGroup.first.m_VertexArray->GetID() != lastUsedVertexArray)
		{
			// restore vertex attribute bindings for this group
			renderableGroup.first.m_VertexArray->Bind();

			lastUsedVertexArray = renderableGroup.first.m_VertexArray->GetID();
		}

		// activate material, if different from current used
		if (renderableGroup.first.m_Material.GetMaterialID() != lastUsedMaterial)
		{
			renderableGroup.first.m_Material.Use();

			//renderableGroup.first.m_Material.SetViewProjectionTransform();
			
			lastUsedMaterial = renderableGroup.first.m_Material.GetMaterialID();
		}

		// render all renderables of current group
		for(auto renderable : renderableGroup.second)
		{
			// apply material
			renderable.m_MaterialComponent->Apply();
			
			// draw shape
			if (renderable.m_ShapeComponent->IsIndexed() == true)
			{
				// draw with indices
				glDrawElements(GL_TRIANGLES, renderable.m_ShapeComponent->GetIndexCount(), VERTEX_INDEX_DATA_TYPE, BUFFER_OFFSET(renderable.m_ShapeComponent->GetIndexDataIndex()));
			}
			else
			{
				// draw without indices
				glDrawArrays(GL_TRIANGLES, 0, renderable.m_ShapeComponent->GetTriangleCount());
			}
		}	

		// Check for errors
		glGetLastError();
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void RenderSystem::PostUpdate(float dt)
{
	// Swap Buffers and bring new rendered OpenGL content to the front
	SDL_GL_SwapWindow(this->m_Window);

	// Check for errors
	glGetLastError();
}


void RenderSystem::SetShapeBufferIndex(ShapeComponent* shapeComponent)
{
	assert(shapeComponent->GetShapeID() != IShape::INVALID_SHAPE && "RenderSystem got Entity with invalid shape.");

	if (this->m_BufferedShapes[shapeComponent->GetShapeID()] != nullptr)
	{
		// set indices
		shapeComponent->SetShapeBufferIndex(*this->m_BufferedShapes[shapeComponent->GetShapeID()]);
		return;
	}

	// Shape is not buffered yet.
	ShapeBufferIndex* bufferIndex = new ShapeBufferIndex;
	this->m_BufferedShapes[shapeComponent->GetShapeID()] = bufferIndex;

	// bind global vertex buffer
	this->m_VertexBuffer->Bind();

	// buffer vertex position data
	{
		assert(shapeComponent->GetPosition() != nullptr && "Invalid shape. Shape has no vertex position data!");
		bufferIndex->m_PositionDataIndex = this->m_VertexBuffer->BufferVertexData(shapeComponent->GetPosition(), VERTEX_POSITION_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// buffer vertex index data
	if(shapeComponent->GetIndexCount() > 0 && shapeComponent->GetIndex() != nullptr)
	{
		this->m_IndexBuffer->Bind();
		{
			bufferIndex->m_IndexDataIndex = this->m_IndexBuffer->BufferIndexData(shapeComponent->GetIndex(), VERTEX_INDEX_DATA_ELEMENT_SIZE * shapeComponent->GetIndexCount());
		}
		this->m_IndexBuffer->Unbind();
	}

	// buffer vertex normal data
	if(shapeComponent->GetNormal() != nullptr)
	{
		bufferIndex->m_NormalDataIndex = this->m_VertexBuffer->BufferVertexData(shapeComponent->GetNormal(), VERTEX_NORMAL_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// buffer vertex uv data
	if (shapeComponent->GetTexCoord() != nullptr)
	{
		bufferIndex->m_TexCoordDataIndex = this->m_VertexBuffer->BufferVertexData(shapeComponent->GetTexCoord(), VERTEX_TEXCOORD_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// buffer vertex color data
	if (shapeComponent->GetColor() != nullptr)
	{
		bufferIndex->m_ColorDataIndex = this->m_VertexBuffer->BufferVertexData(shapeComponent->GetColor(), VERTEX_COLOR_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// unbind global vertex buffer
	this->m_VertexBuffer->Unbind();

	// set indices
	shapeComponent->SetShapeBufferIndex(*bufferIndex);
}

void RenderSystem::RegisterRenderable(const ECS::EntityId id, const MaterialComponent* material, const ShapeComponent* shape)
{
	const RenderableGroupID RGID = CreateRenderableGroupID(material, shape);

	// check if there is already a group for this renderable
	for (auto it : this->m_RenderableGroups)
	{
		if (it.first.m_GroupID == RGID)
		{
			// place renderable in this group
			it.second.push_back(Renderable(id, material, shape));
			return;
		}
	}
	
	// There is no group for this renderable yet, create a new one
	RenderableGroup renderableGroup(RGID, *material);
	{
		// Configure render state
		renderableGroup.m_VertexArray->Bind();
		{
			// bind global vertex buffer
			this->m_VertexBuffer->Bind();

			// buffer vertex position data
			MaterialVertexAttributeLoc positionVertexAttribute = material->GetPositionVertexAttributeLocation();
			assert(positionVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC && "Material of a renderable does not provide a position vertex attribute!");

			glEnableVertexAttribArray(positionVertexAttribute);
			glVertexAttribPointer(positionVertexAttribute, VERTEX_POSITION_DATA_ELEMENT_LEN, VERTEX_POSITION_DATA_TYPE, GL_FALSE, 0, BUFFER_OFFSET(shape->GetPositionDataIndex()));

			// buffer vertex index data
			if (shape->GetIndexCount() > 0 && shape->GetIndex() != nullptr)
			{
				this->m_IndexBuffer->Bind();
			}

			// buffer vertex normal data
			MaterialVertexAttributeLoc normalVertexAttribute = material->GetNormalVertexAttributeLocation();
			if (shape->GetNormal() != nullptr && normalVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
			{
				glEnableVertexAttribArray(normalVertexAttribute);
				glVertexAttribPointer(normalVertexAttribute, VERTEX_NORMAL_DATA_ELEMENT_LEN, VERTEX_NORMAL_DATA_TYPE, GL_FALSE, 0, BUFFER_OFFSET(shape->GetNormalDataIndex()));
			}

			// buffer vertex uv data
			MaterialVertexAttributeLoc texCoordVertexAttribute = material->GetTexCoordVertexAttributeLocation();
			if (shape->GetTexCoord() != nullptr && texCoordVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
			{
				glEnableVertexAttribArray(texCoordVertexAttribute);
				glVertexAttribPointer(texCoordVertexAttribute, VERTEX_TEXCOORD_DATA_ELEMENT_LEN, VERTEX_TEXCOORD_DATA_TYPE, GL_FALSE, 0, BUFFER_OFFSET(shape->GetTexCoordDataIndex()));
			}

			// buffer vertex color data
			MaterialVertexAttributeLoc colorVertexAttribute = material->GetColorVertexAttributeLocation();
			if (shape->GetColor() != nullptr && colorVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
			{
				glEnableVertexAttribArray(colorVertexAttribute);
				glVertexAttribPointer(colorVertexAttribute, VERTEX_COLOR_DATA_ELEMENT_LEN, VERTEX_COLOR_DATA_TYPE, GL_FALSE, 0, BUFFER_OFFSET(shape->GetColorDataIndex()));
			}
		}
		renderableGroup.m_VertexArray->Unbind();

		this->m_VertexBuffer->Unbind();
		this->m_IndexBuffer->Unbind();
	}
	this->m_RenderableGroups[renderableGroup].push_back(Renderable(id, material, shape));
}

void RenderSystem::UnregisterRenderable(const ECS::EntityId id, const MaterialComponent* material, const ShapeComponent* shape)
{
	const RenderableGroupID RGID = CreateRenderableGroupID(material, shape);

	RenderableList& group = this->m_RenderableGroups[RGID];
	for (RenderableList::iterator it = group.begin(); it != group.end(); ++it)
	{
		if (it->m_EntityId == id)
		{
			group.erase(it);
			return;
		}
	}

	assert(false && "RenderableGroups corrupted!");
}

void RenderSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&RenderSystem::OnWindowResized);
	RegisterEventCallback(&RenderSystem::OnWindowMinimized);
	RegisterEventCallback(&RenderSystem::OnWindowRestored);

	RegisterEventCallback(&RenderSystem::OnEntityCreated);
	RegisterEventCallback(&RenderSystem::OnEntityDestroyed);
}

void RenderSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&RenderSystem::OnWindowResized);
	UnregisterEventCallback(&RenderSystem::OnWindowMinimized);
	UnregisterEventCallback(&RenderSystem::OnWindowRestored);

	UnregisterEventCallback(&RenderSystem::OnEntityCreated);
	UnregisterEventCallback(&RenderSystem::OnEntityDestroyed);
}


void RenderSystem::OnWindowResized(const WindowResizedEvent* event)
{
	glViewport(0, 0, event->width, event->height);
}

void RenderSystem::OnWindowMinimized(const WindowMinimizedEvent* event)
{
	// save render context
}

void RenderSystem::OnWindowRestored(const WindowRestoredEvent* event)
{
	// restore render context
}

void RenderSystem::OnEntityCreated(const ECS::EntityCreated* event)
{
	// Get Entity
	ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->m_EntityID);
	assert(entity != nullptr && "Failed to retrieve entity by id!");

	// get entities material and shape component
	const MaterialComponent*	materialComponent	= entity->GetComponent<MaterialComponent>();
	const ShapeComponent*		shapeComponent		= entity->GetComponent<ShapeComponent>();

	// If there is one of the components missing we can stop, there is nothing todo for the renderer
	if (materialComponent == nullptr || shapeComponent == nullptr)
		return;

	// Set shape's data buffer indices
	SetShapeBufferIndex(const_cast<ShapeComponent*>(shapeComponent));
	
	// Register entity as new renderable
	RegisterRenderable(event->m_EntityID, materialComponent, shapeComponent);
}

void RenderSystem::OnEntityDestroyed(const ECS::EntityDestroyed* event)
{
	// Get Entity
	ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->m_EntityID);
	assert(entity != nullptr && "Failed to retrieve entity by id!");

	// get entities material and shape component
	const MaterialComponent*	materialComponent = entity->GetComponent<MaterialComponent>();
	const ShapeComponent*		shapeComponent = entity->GetComponent<ShapeComponent>();

	// If there is one of the components missing we can stop, there is nothing todo for the renderer
	if (materialComponent == nullptr || shapeComponent == nullptr)
		return;

	UnregisterRenderable(event->m_EntityID, materialComponent, shapeComponent);
}