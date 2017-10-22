///-------------------------------------------------------------------------------------------------
/// File:	Game.cpp.
///
/// Summary:	Implements the game application class.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

Game::Game(const char* name) :
	mGameTitle(name),
	m_Window(nullptr),
	m_Fullscreen(false),
	m_WindowPosX(-1), m_WindowPosY(-1),
	m_WindowWidth(-1), m_WindowHeight(-1)
{}

Game::~Game()
{}


void Game::InitializeECS()
{
	// start the engine
	ECS::Initialize();
}

void Game::InitializeSDL()
{
	// Initialize SDL 2.0
	SDL_Init(SDL_INIT_VIDEO);

	// Create a new window for OpenGL rendering prupose
	this->m_Window = SDL_CreateWindow(this->mGameTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->m_WindowWidth, this->m_WindowHeight, SDL_WINDOW_OPENGL | (this->m_Fullscreen ? SDL_WINDOW_FULLSCREEN : (0)));
	if (m_Window == 0) {

		SDL_Log("Unable to create game application window! %s", SDL_GetError());
		exit(-1);
	}

	// Place and resize application window
	SDL_GetWindowPosition(this->m_Window, &this->m_WindowPosX, &this->m_WindowPosY);
	SDL_GetWindowSize(this->m_Window, &this->m_WindowWidth, &this->m_WindowHeight);
}


void Game::Initialize(int width, int height, bool fullscreen) 
{

	this->m_WindowWidth		= width;
	this->m_WindowHeight	= height;
	this->m_Fullscreen		= fullscreen;

	// Set initial FSM state
	ChangeState(GameState::INITIALIZED);
}

void Game::Terminate()
{
	// Terminate ECS
	ECS::Terminate();

	// Destroy window
	if (this->m_Window)
		SDL_DestroyWindow(this->m_Window);

	// Terminate SDL
	SDL_Quit();

	// this will break the main game loop.
	this->m_Window = nullptr;
}

void Game::ProcessWindowEvent()
{
	// Pump all SDL events to queue
	SDL_PumpEvents();

	SDL_Event event;
	while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)) {

		switch (event.window.event) 
		{
			case SDL_WINDOWEVENT_SHOWN:
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				break;
			case SDL_WINDOWEVENT_MOVED:
				break;
			case SDL_WINDOWEVENT_RESIZED:
				ECS::ECS_Engine->SendEvent<WindowResizedEvent>(event.window.data1, event.window.data2);
				break;

			case SDL_WINDOWEVENT_SIZE_CHANGED:
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				ECS::ECS_Engine->SendEvent<WindowMinimizedEvent>();
				break;

			case SDL_WINDOWEVENT_MAXIMIZED:
				break;
			case SDL_WINDOWEVENT_RESTORED:
				ECS::ECS_Engine->SendEvent<WindowRestoredEvent>();
				break;

			case SDL_WINDOWEVENT_ENTER:
				break;
			case SDL_WINDOWEVENT_LEAVE:
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				break;
			case SDL_WINDOWEVENT_CLOSE:
				this->Terminate();
				return;

#if SDL_VERSION_ATLEAST(2, 0, 5)
			case SDL_WINDOWEVENT_TAKE_FOCUS:
				break;
			case SDL_WINDOWEVENT_HIT_TEST:
				break;
#endif
		}
	}
}

void Game::ToggleFullscreen() {

	if(m_Fullscreen == false)
		ECS::ECS_Engine->SendEvent<EnterFullscreenModeEvent>();
	else
		ECS::ECS_Engine->SendEvent<EnterWindowModeEvent>();

	m_Fullscreen = !m_Fullscreen;
	SDL_SetWindowFullscreen(m_Window, m_Fullscreen);
}

void Game::Run()
{
	// Window will be nulled, when Game changes to 'TERMINATED' game state
	while (this->m_Window != nullptr)
	{
		// Process game application window events
		ProcessWindowEvent();
		if (this->m_Window == nullptr)
			return;

		// Update the ECS
		ECS::ECS_Engine->Update(DELTA_TIME_STEP);

		// Update Game
		this->UpdateStateMachine();

		// Update FPS counter
		this->m_FPS.Update();
		SDL_SetWindowTitle(this->m_Window, std::to_string(this->m_FPS.GetFPS()).c_str());

	}; // MAIN GAME LOOP!

	int i = 0;
}