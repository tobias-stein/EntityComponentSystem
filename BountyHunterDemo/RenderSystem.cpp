///-------------------------------------------------------------------------------------------------
/// File:	RenderSystem.cpp.
///
/// Summary:	Implements the render system class.
///-------------------------------------------------------------------------------------------------

#include "RenderSystem.h"

RenderSystem::RenderSystem(SDL_Window* window) :
	m_Window(window)
{
	InitializeOpenGL();
	RegisterEventCallbacks();
}

RenderSystem::~RenderSystem()
{
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


void RenderSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&RenderSystem::OnWindowResized);
	RegisterEventCallback(&RenderSystem::OnWindowMinimized);
	RegisterEventCallback(&RenderSystem::OnWindowRestored);
}

void RenderSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&RenderSystem::OnWindowResized);
	UnregisterEventCallback(&RenderSystem::OnWindowMinimized);
	UnregisterEventCallback(&RenderSystem::OnWindowRestored);
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