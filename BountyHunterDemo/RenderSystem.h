///-------------------------------------------------------------------------------------------------
/// File:	RenderSystem.h.
///
/// Summary:	Declares the render system that will be responsible for opengl rendering.
///-------------------------------------------------------------------------------------------------

#ifndef __RENDER_SYSTEM_H__
#define __RENDER_SYSTEM_H__

#include <ECS.h>
#include <SDL.h>

#include "OpenGL.h"
#include "GameEvents.h"

class RenderSystem : public ECS::System<RenderSystem>, protected ECS::Event::IEventListener
{
private:
	
	// Application window
	SDL_Window*		m_Window;

	// Render context
	SDL_GLContext	m_Context;

private:

	void InitializeOpenGL();
	void TerminateOpenGL();

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	// Event callbacks
	void OnWindowResized(const WindowResizedEvent* event);
	void OnWindowMinimized(const WindowMinimizedEvent* event);
	void OnWindowRestored(const WindowRestoredEvent* event);

public:

	RenderSystem(SDL_Window* window);
	~RenderSystem();

	virtual void PreUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void PostUpdate(float dt) override;

}; // class RenderSystem

#endif // __RENDER_SYSTEM_H__
