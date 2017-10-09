///-------------------------------------------------------------------------------------------------
/// File:	RenderSystem.h.
///
/// Summary:	Declares the render system that will be responsible for opengl rendering.
///-------------------------------------------------------------------------------------------------

#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__



#include <ECS/ECS.h>
#include <SDL.h>

#include <unordered_map>
#include <list>

#include "GLBuffer.h"
#include "GLShader.h"
#include "RenderableGroup.h"

#include "GameEvents.h"

#include "Shape.h"
#include "ShapeBufferIndex.h"

#include "TransformComponent.h"
#include "ShapeComponent.h"
#include "MaterialComponent.h"


class RenderSystem : public ECS::System<RenderSystem>, protected ECS::Event::IEventListener
{
	static constexpr size_t		GLOBAL_VERTEX_BUFFER_SIZE { 8388608 /* 8 MB */ };
	static constexpr size_t		GLOBAL_INDEX_BUFFER_SIZE  { 8388608 /* 8 MB */ };

	static inline const RenderableGroupID CreateRenderableGroupID(MaterialComponent* material, ShapeComponent* shape)
	{
		return ((material->GetMaterialID() << 16) | shape->GetShapeID());
	}

	using BufferedShapes = std::vector<ShapeBufferIndex*>;


	struct Renderable
	{
		const ECS::EntityId		m_EntityId;
		
		TransformComponent*		m_TransformComponent;
		ShapeComponent*			m_ShapeComponent;
		MaterialComponent*		m_MaterialComponent;
		

		Renderable(const ECS::EntityId id, TransformComponent* transform, MaterialComponent* material, ShapeComponent* shape) :
			m_EntityId(id),
			m_TransformComponent(transform),
			m_MaterialComponent(material),
			m_ShapeComponent(shape)
		{}

		~Renderable()
		{
			this->m_TransformComponent = nullptr;
			this->m_MaterialComponent = nullptr;
			this->m_ShapeComponent = nullptr;
		}
	};

	using RenderableList = std::list<Renderable>;
	using RenderableGroups = std::unordered_map<RenderableGroup, RenderableList>;

private:
	
	// Application window
	SDL_Window*			m_Window;

	// Render context
	SDL_GLContext		m_Context;

	// Global Vertex and Index Buffer
	VertexBuffer*		m_VertexBuffer;
	IndexBuffer*		m_IndexBuffer;

	// Keeps track of already buffered shapes
	BufferedShapes		m_BufferedShapes;

	// A set of all currently registered randerable entities
	RenderableGroups	m_RenderableGroups;

private:

	void InitializeOpenGL();
	void TerminateOpenGL();

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void RenderSystem::SetShapeBufferIndex(ShapeComponent* shapeComponent);
	///
	/// Summary:	This method sets the appropriate start indices for all vertex data attributes stored
	/// in the global vertex buffer. If shape data is not buffered yet, than its data is stored first.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	7/10/2017
	///
	/// Parameters:
	/// shapeComponent - 	[in,out] If non-null, the shape component.
	///-------------------------------------------------------------------------------------------------

	void SetShapeBufferIndex(ShapeComponent* shapeComponent);

	void RegisterRenderable(const ECS::EntityId id, TransformComponent* transform, MaterialComponent* material, ShapeComponent* shape);
	void UnregisterRenderable(const ECS::EntityId id, MaterialComponent* material, ShapeComponent* shape);

	// Event callbacks
	void OnWindowResized(const WindowResizedEvent* event);
	void OnWindowMinimized(const WindowMinimizedEvent* event);
	void OnWindowRestored(const WindowRestoredEvent* event);

	void OnEntityCreated(const ECS::EntityCreated* event);
	void OnEntityDestroyed(const ECS::EntityDestroyed* event);

public:

	RenderSystem(SDL_Window* window);
	~RenderSystem();

	virtual void PreUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void PostUpdate(float dt) override;

}; // class RenderSystem

#endif // __RENDER_SYSTEM_H__
