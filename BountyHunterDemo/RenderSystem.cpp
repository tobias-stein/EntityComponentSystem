///-------------------------------------------------------------------------------------------------
/// File:	RenderSystem.cpp.
///
/// Summary:	Implements the render system class.
///-------------------------------------------------------------------------------------------------

#include "RenderSystem.h"

RenderSystem::RenderSystem(SDL_Window* window) :
	m_Window(window),
	m_ActiveCamera(nullptr),
	m_BufferedShapes(IShape::MAX_SHAPES, nullptr),
	m_DrawDebug(false)
{
	InitializeOpenGL();

	// DEBUG DRAWING
	this->m_DebugLineRenderer = new GLLineRenderer();

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
	
	// DEBUG DRAWING
	delete this->m_DebugLineRenderer;
	this->m_DebugLineRenderer = nullptr;

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

	// set viewport
	int width, height;
	SDL_GetWindowSize(this->m_Window, &width, &height);
	glViewport(0, 0, width, height);

	// Clear framebuffer with black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// transparency
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Check for errors.
	glGetLastError();
}

void RenderSystem::TerminateOpenGL()
{

	glUseProgram(0);

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
	if (this->m_ActiveCamera == nullptr)
	{
		SDL_LogError(SDL_LOG_PRIORITY_ERROR, "RenderSystem has no active camera!");
		return;
	}

	MaterialID		lastUsedMaterial	= INVALID_MATERIAL_ID;
	VertexArrayID	lastUsedVertexArray = -1;

	for (auto& renderableGroup : this->m_RenderableGroups)
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

			// Set active camera's view and projection matrix
			((RenderableGroup)(renderableGroup.first)).m_Material.SetViewProjectionTransform(this->m_ActiveCamera->GetViewTransform(), this->m_ActiveCamera->GetProjectionTransform());
			
			lastUsedMaterial = renderableGroup.first.m_Material.GetMaterialID();
		}

		// render all renderables of current group
		for(auto renderable : renderableGroup.second)
		{
			// ignore disables renderables
			if (renderable.m_GameObject->IsActive() == false && renderable.m_MaterialComponent->IsActive() == true && renderable.m_ShapeComponent->IsActive() == true)
				continue;
			
			// apply material
			renderable.m_MaterialComponent->Apply();

			// Set model transform uniform
			renderable.m_MaterialComponent->SetModelTransform(renderable.m_TransformComponent->AsFloat());

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

	// DEBUG DRAWING
	if (DEBUG_DRAWING_ENABLED == true)
	{
		// render all lines
		this->m_DebugLineRenderer->Flush(this->m_ActiveCamera->GetProjectionTransform(), this->m_DrawDebug);
	}
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

void RenderSystem::RegisterRenderable(ECS::IEntity* entity, TransformComponent* transform, MaterialComponent* material, ShapeComponent* shape)
{
	const RenderableGroupID RGID = CreateRenderableGroupID(material, shape);

	// check if there is already a group for this renderable
	for (auto it : this->m_RenderableGroups)
	{
		if (it.first.m_GroupID == RGID)
		{
			// place renderable in this group
			this->m_RenderableGroups[RGID].push_back(Renderable(entity, transform, material, shape));
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
	this->m_RenderableGroups[renderableGroup].push_back(Renderable(entity, transform, material, shape));
}

void RenderSystem::UnregisterRenderable(GameObjectId gameObjectId)
{
	for (auto& RG : this->m_RenderableGroups)
	{
		for (RenderableList::iterator it = RG.second.begin(); it != RG.second.end(); ++it)
		{
			if (it->m_GameObject->GetEntityID() == gameObjectId)
			{
				RG.second.erase(it);
				return;
			}
		}
	}
}

void RenderSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&RenderSystem::OnWindowResized);
	RegisterEventCallback(&RenderSystem::OnWindowMinimized);
	RegisterEventCallback(&RenderSystem::OnWindowRestored);

	RegisterEventCallback(&RenderSystem::OnGameObjectCreated);
	RegisterEventCallback(&RenderSystem::OnGameObjectDestroyed);

	RegisterEventCallback(&RenderSystem::OnCameraCreated);
	RegisterEventCallback(&RenderSystem::OnCameraDestroyed);

	RegisterEventCallback(&RenderSystem::OnToggleDebugDraw);
}

void RenderSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&RenderSystem::OnWindowResized);
	UnregisterEventCallback(&RenderSystem::OnWindowMinimized);
	UnregisterEventCallback(&RenderSystem::OnWindowRestored);

	UnregisterEventCallback(&RenderSystem::OnGameObjectCreated);
	UnregisterEventCallback(&RenderSystem::OnGameObjectDestroyed);

	UnregisterEventCallback(&RenderSystem::OnCameraCreated);
	UnregisterEventCallback(&RenderSystem::OnCameraDestroyed);

	UnregisterEventCallback(&RenderSystem::OnToggleDebugDraw);
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

void RenderSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
	// Get Entity
	ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->m_EntityID);
	assert(entity != nullptr && "Failed to retrieve entity by id!");

	// get entities material and shape component
	TransformComponent*	transformComponent	= entity->GetComponent<TransformComponent>();
	MaterialComponent*	materialComponent	= entity->GetComponent<MaterialComponent>();
	ShapeComponent*		shapeComponent		= entity->GetComponent<ShapeComponent>();

	// If there is one of the components missing we can stop, there is nothing todo for the renderer
	if (transformComponent == nullptr || materialComponent == nullptr || shapeComponent == nullptr)
		return;

	// Set shape's data buffer indices
	SetShapeBufferIndex(const_cast<ShapeComponent*>(shapeComponent));
	
	// Register entity as new renderable
	RegisterRenderable(entity, transformComponent, materialComponent, shapeComponent);
}

void RenderSystem::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
	UnregisterRenderable(event->m_EntityID);
}

void RenderSystem::OnCameraCreated(const CameraCreated* event)
{
	if (this->m_ActiveCamera == nullptr)
	{
		ECS::IEntity* camera = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->cameraID);
		if (camera != nullptr)
		{
			/*
			note: dynamic_cast here, because we are doing a down-cast

			   IEntity
			      |
		      GameObject   IGameCamera
			      |            |
		      GameCamera ------+
			      |
			 SpecificCamera
			*/
			this->m_ActiveCamera = dynamic_cast<IGameCamera*>(camera);

			assert(this->m_ActiveCamera != nullptr && "RenderSystem failed to set active camera!");
			SDL_Log("Camera (ID: %d) set as default active camera for RenderSystem.");
		}
	}
}

void RenderSystem::OnCameraDestroyed(const CameraDestroyed* event)
{
	if (event->cameraID == this->m_ActiveCamera->GetCameraID())
	{
		this->m_ActiveCamera = nullptr;
		SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "Warning RenderSystems active camera got destroyed!");
	}
}

void RenderSystem::OnToggleDebugDraw(const ToggleDebugDrawEvent * event)
{
	this->m_DrawDebug = !this->m_DrawDebug;
}


void RenderSystem::DrawLine(Position2D p0, Position2D p1, bool arrowHead0, bool arrowHead1, Color3f color)
{
	if (DEBUG_DRAWING_ENABLED == true)
	{
		this->m_DebugLineRenderer->AddLine(Position(p0, -1.0f), Position(p1, -1.0f), color);

		if (arrowHead0 == true)
		{
			glm::vec2 dirNorm = glm::normalize(p1 - p0);
			glm::vec2 perp = glm::vec2(-dirNorm.y, dirNorm.x);

			this->m_DebugLineRenderer->AddLine(Position(p0, -1.0f), Position(p0 + dirNorm - perp, -1.0f), color);
			this->m_DebugLineRenderer->AddLine(Position(p0, -1.0f), Position(p0 + dirNorm + perp, -1.0f), color);
		}

		if (arrowHead1 == true)
		{
			glm::vec2 dirNorm = glm::normalize(p0 - p1);
			glm::vec2 perp = glm::vec2(-dirNorm.y, dirNorm.x);

			this->m_DebugLineRenderer->AddLine(Position(p1, -1.0f), Position(p1 + dirNorm - perp, -1.0f), color);
			this->m_DebugLineRenderer->AddLine(Position(p1, -1.0f), Position(p1 + dirNorm + perp, -1.0f), color);
		}
	}
}

void RenderSystem::DrawCircle(Position2D center, float radius, Color3f color)
{
	if (DEBUG_DRAWING_ENABLED == true)
	{
		const float NUM_SEGMENTS = 16.0f;

		const float STEP = glm::two_pi<float>() / NUM_SEGMENTS;

		float c = glm::cos(STEP);
		float s = glm::sin(STEP);

		glm::vec2 r1(1.0f, 0.0f);
		glm::vec2 v1 = center + radius * r1;

		for (size_t i = 0; i < NUM_SEGMENTS; ++i)
		{
			glm::vec2 r2;

			r2.x = c * r1.x - s * r1.y;
			r2.y = s * r1.x + c * r1.y;
			glm::vec2 v2 = center + radius * r2;

			this->m_DebugLineRenderer->AddLine(glm::vec3(v1, -1.0f), glm::vec3(v2, -1.0f), color);

			r1 = r2;
			v1 = v2;
		}
	}
}

void RenderSystem::DrawSegment(Position2D center, float radius, float start, float end, Color3f color)
{
	if (DEBUG_DRAWING_ENABLED == true)
	{
		const float NUM_SEGMENTS = 16.0f;

		const float STEP = (end - start) / NUM_SEGMENTS;

		float c = glm::cos(STEP);
		float s = glm::sin(STEP);

		glm::vec2 r1(glm::cos(start), glm::sin(start));
		glm::vec2 v1 = center + radius * r1;

		this->m_DebugLineRenderer->AddLine(glm::vec3(center, -1.0f), glm::vec3(v1, -1.0f), color);

		for (size_t i = 0; i < NUM_SEGMENTS; ++i)
		{
			glm::vec2 r2;

			r2.x = c * r1.x - s * r1.y;
			r2.y = s * r1.x + c * r1.y;
			glm::vec2 v2 = center + radius * r2;

			this->m_DebugLineRenderer->AddLine(glm::vec3(v1, -1.0f), glm::vec3(v2, -1.0f), color);

			r1 = r2;
			v1 = v2;
		}

		this->m_DebugLineRenderer->AddLine(glm::vec3(center, -1.0f), glm::vec3(v1, -1.0f), color);
	}
}

void RenderSystem::DrawRectangle(Position2D minCorner, Position2D maxCorner, Color3f color)
{
	if (DEBUG_DRAWING_ENABLED == true)
	{
		const float w = maxCorner.x - minCorner.x;
		const float h = maxCorner.y - minCorner.y;

		// left
		this->m_DebugLineRenderer->AddLine(glm::vec3(minCorner, -1.0f), glm::vec3(minCorner.x, minCorner.y + h, -1.0f), color);

		// right
		this->m_DebugLineRenderer->AddLine(glm::vec3(maxCorner, -1.0f), glm::vec3(maxCorner.x, maxCorner.y - h, -1.0f), color);

		// top
		this->m_DebugLineRenderer->AddLine(glm::vec3(maxCorner, -1.0f), glm::vec3(maxCorner.x - w, maxCorner.y, -1.0f), color);

		// bottom
		this->m_DebugLineRenderer->AddLine(glm::vec3(minCorner, -1.0f), glm::vec3(minCorner.x + w, minCorner.y, -1.0f), color);
	}
}

void RenderSystem::DrawRectangle(Position2D center, float halfExpWidth, float halfExpHeight, Color3f color)
{
	if (DEBUG_DRAWING_ENABLED == true)
	{
		// left
		this->m_DebugLineRenderer->AddLine(glm::vec3(center.x - halfExpWidth, center.x - halfExpHeight, -1.0f), glm::vec3(center.x - halfExpWidth, center.x + halfExpHeight, -1.0f), color);

		// right
		this->m_DebugLineRenderer->AddLine(glm::vec3(center.x + halfExpWidth, center.x - halfExpHeight, -1.0f), glm::vec3(center.x + halfExpWidth, center.x + halfExpHeight, -1.0f), color);

		// top
		this->m_DebugLineRenderer->AddLine(glm::vec3(center.x - halfExpWidth, center.x + halfExpHeight, -1.0f), glm::vec3(center.x + halfExpWidth, center.x + halfExpHeight, -1.0f), color);

		// bottom
		this->m_DebugLineRenderer->AddLine(glm::vec3(center.x - halfExpWidth, center.x - halfExpHeight, -1.0f), glm::vec3(center.x + halfExpWidth, center.x - halfExpHeight, -1.0f), color);
	}
}
