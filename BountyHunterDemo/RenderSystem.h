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

#include "GameCamera.h"

#include "GLLineRenderer.h"

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
		GameObjectId			m_GameObjectId;
		ECS::IEntity*			m_GameObject;
		
		TransformComponent*		m_TransformComponent;
		ShapeComponent*			m_ShapeComponent;
		MaterialComponent*		m_MaterialComponent;
		

		Renderable(ECS::IEntity* entity, TransformComponent* transform, MaterialComponent* material, ShapeComponent* shape) :
			m_GameObjectId(entity->GetEntityID()),
			m_GameObject(entity),
			m_TransformComponent(transform),
			m_MaterialComponent(material),
			m_ShapeComponent(shape)
		{}

		~Renderable()
		{
			this->m_GameObjectId = INVALID_GAMEOBJECT_ID;
			this->m_GameObject = nullptr;
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

	// Active Camera
	IGameCamera*		m_ActiveCamera;

	// DEBUG DRAWING
	bool				m_DrawDebug;
	GLLineRenderer*		m_DebugLineRenderer;

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

	void RegisterRenderable(ECS::IEntity* entity, TransformComponent* transform, MaterialComponent* material, ShapeComponent* shape);
	void UnregisterRenderable(GameObjectId gameObjectId);

	// Event callbacks
	void OnWindowResized(const WindowResizedEvent* event);
	void OnWindowMinimized(const WindowMinimizedEvent* event);
	void OnWindowRestored(const WindowRestoredEvent* event);

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);

	void OnCameraCreated(const CameraCreated* event);
	void OnCameraDestroyed(const CameraDestroyed* event);

	void OnToggleDebugDraw(const ToggleDebugDrawEvent* event);

public:

	RenderSystem(SDL_Window* window);
	~RenderSystem();

	virtual void PreUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void PostUpdate(float dt) override;

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// void RenderSystem::DrawLine(Position2D p0, Position2D p1, Color3f color0 = Color3f(1.0f),
	/// bool arrowHead0 = false, bool arrowHead1 = false);
	///
	/// Summary: Draws a 2D line from 'p0' to 'p1'. A RGB color can be specified as well as a starting and/or
	/// closing arrow head on line start/end.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	26/10/2017
	///
	/// Parameters:
	/// p0 - 		 	The p 0.
	/// p1 - 		 	The first Position2D.
	/// color0 - 	 	(Optional) The color 0.
	/// arrowHead0 - 	(Optional) True to arrow head 0.
	/// arrowHead1 - 	(Optional) True to arrow head 1.
	///-------------------------------------------------------------------------------------------------

	void DrawLine(Position2D p0, Position2D p1, bool arrowHead0 = false, bool arrowHead1 = false, Color3f color = Color3f(1.0f));

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// void RenderSystem::DrawCircle(Position2D center, float radius,
	/// Color3f color0 = Color3f(1.0f));
	///
	/// Summary:	Draws a full circle.
	///
	/// Author:	Tobias Stein.
	///
	/// Date:	26/10/2017.
	///
	/// Parameters:
	/// center -   	The center.
	/// radius -   	The radius.
	/// color0 -   	(Optional) The color 0.
	///-------------------------------------------------------------------------------------------------

	void DrawCircle(Position2D center, float radius, Color3f color = Color3f(1.0f));

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// void RenderSystem::DrawSegment(Position2D center, float radius, float start, float end,
	/// Color3f color0 = Color3f(1.0f));
	///
	/// Summary:	Draws a segment, which is sort of semi circle.
	///
	/// Author:	Tobias Stein.
	///
	/// Date:	26/10/2017.
	///
	/// Parameters:
	/// center -   	The center.
	/// radius -   	The radius.
	/// start -    	The start.
	/// end - 	   	The end.
	/// color0 -   	(Optional) The color 0.
	///-------------------------------------------------------------------------------------------------

	void DrawSegment(Position2D center, float radius, float start, float end, Color3f color = Color3f(1.0f));

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// void RenderSystem::DrawRectangle(Position2D minCorner, Position2D maxCorner,
	/// Color3f color0 = Color3f(1.0f));
	///
	/// Summary:	Draws rectangle specified by its min and max corner points.
	///
	/// Author:	Tobias Stein.
	///
	/// Date:	26/10/2017.
	///
	/// Parameters:
	/// minCorner - 	The minimum corner.
	/// maxCorner - 	The maximum corner.
	/// color0 -    	(Optional) The color 0.
	///-------------------------------------------------------------------------------------------------

	void DrawRectangle(Position2D minCorner, Position2D maxCorner, Color3f color = Color3f(1.0f));

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// void RenderSystem::DrawRectangle(Position2D center, float halfExpWidth, float halfExpHeight,
	/// Color3f color0 = Color3f(1.0f));
	///
	/// Summary:	Draws rectangle specified by a center position and helf expanding width and height.
	///
	/// Author:	Tobias Stein.
	///
	/// Date:	26/10/2017.
	///
	/// Parameters:
	/// center - 			The center.
	/// halfExpWidth -  	Width of the half exponent.
	/// halfExpHeight - 	Height of the half exponent.
	/// color0 - 			(Optional) The color 0.
	///-------------------------------------------------------------------------------------------------

	void DrawRectangle(Position2D center, float halfExpWidth, float halfExpHeight, Color3f color = Color3f(1.0f));


}; // class RenderSystem

#endif // __RENDER_SYSTEM_H__
