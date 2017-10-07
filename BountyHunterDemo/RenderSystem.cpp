///-------------------------------------------------------------------------------------------------
/// File:	RenderSystem.cpp.
///
/// Summary:	Implements the render system class.
///-------------------------------------------------------------------------------------------------

#include "RenderSystem.h"

RenderSystem::RenderSystem(SDL_Window* window) :
	m_Window(window),
	m_VertexBuffer(GLOBAL_VERTEX_BUFFER_SIZE),
	m_IndexBuffer(GLOBAL_INDEX_BUFFER_SIZE),
	m_BufferedShapes(IShape::MAX_SHAPES, nullptr)
{
	InitializeOpenGL();
	RegisterEventCallbacks();
}

RenderSystem::~RenderSystem()
{
	for (size_t i = 0; i < this->m_BufferedShapes.size(); ++i)
	{
		delete this->m_BufferedShapes[i];
		this->m_BufferedShapes[i] = nullptr;
	}
	this->m_BufferedShapes.clear();

	UnregisterEventCallbacks();
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
	// Check for errors
	glGetLastError();
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
	this->m_VertexBuffer.Bind();

	// buffer vertex position data
	{
		assert(shapeComponent->GetPosition() != nullptr && "Invalid shape. Shape has no vertex position data!");
		bufferIndex->m_PositionDataIndex = this->m_VertexBuffer.BufferVertexData(shapeComponent->GetPosition(), SHAPE_VERTEX_POSITION_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// buffer vertex index data
	if(shapeComponent->GetIndexCount() > 0 && shapeComponent->GetIndex() != nullptr)
	{
		this->m_IndexBuffer.Bind();
		{
			bufferIndex->m_IndexDataIndex = this->m_IndexBuffer.BufferIndexData(shapeComponent->GetIndex(), SHAPE_VERTEX_INDEX_DATA_ELEMENT_SIZE * shapeComponent->GetIndexCount());
		}
		this->m_IndexBuffer.Unbind();
	}

	// buffer vertex normal data
	if(shapeComponent->GetNormal() != nullptr)
	{
		bufferIndex->m_NormalDataIndex = this->m_VertexBuffer.BufferVertexData(shapeComponent->GetNormal(), SHAPE_VERTEX_NORMAL_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// buffer vertex uv data
	if (shapeComponent->GetUV() != nullptr)
	{
		bufferIndex->m_UVDataIndex = this->m_VertexBuffer.BufferVertexData(shapeComponent->GetUV(), SHAPE_VERTEX_UV_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// buffer vertex color data
	if (shapeComponent->GetColor() != nullptr)
	{
		bufferIndex->m_ColorDataIndex = this->m_VertexBuffer.BufferVertexData(shapeComponent->GetColor(), SHAPE_VERTEX_COLOR_DATA_ELEMENT_SIZE * shapeComponent->GetVertexCount());
	}

	// unbind global vertex buffer
	this->m_VertexBuffer.Unbind();

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
	RenderableGroup renderableGroup(RGID);
	{
		// Configure render state
		renderableGroup.m_VertexArray.Bind();
		{
			// bind global vertex buffer
			this->m_VertexBuffer.Bind();

			// buffer vertex position data


			// buffer vertex index data
			if (shape->GetIndexCount() > 0 && shape->GetIndex() != nullptr)
			{
				this->m_IndexBuffer.Bind();

			}

			// buffer vertex normal data
			if (shape->GetNormal() != nullptr)
			{
			}

			// buffer vertex uv data
			if (shape->GetUV() != nullptr)
			{
			}

			// buffer vertex color data
			if (shape->GetColor() != nullptr)
			{
			}
		}
		renderableGroup.m_VertexArray.Unbind();

		this->m_VertexBuffer.Unbind();
		this->m_IndexBuffer.Unbind();
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
		UnregisterRenderable(event->m_EntityID, materialComponent, shapeComponent);
}