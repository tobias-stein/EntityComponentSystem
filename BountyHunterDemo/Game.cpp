///-------------------------------------------------------------------------------------------------
/// File:	Game.cpp.
///
/// Summary:	Implements the game application class.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

#include "InputSystem.h"

Game::Game() :
	mAppState(NOT_INITIALIZED),
	mWindow(nullptr),
	mFullscreen(false),
	mWindowX(-1),
	mWindowY(-1),
	mWindowW(-1),
	mWindowH(-1)
{}

Game::~Game()
{}


void Game::InitializeECS()
{
	ECS::Initialize();

	// Create and initialize systems
	{
		ECS::ECS_Engine->GetSystemManager()->AddSystem<InputSystem>();
		ECS::ECS_Engine->GetSystemManager()->SetSystemPriority<InputSystem>(ECS::HIGH_SYSTEM_PRIORITY);
	}

	// Add system dependencies
	{
	}
}

void Game::InitializeSDL(const char* title, int width, int height, bool fullscreen)
{
	// Initialize SDL 2.0
	SDL_Init(SDL_INIT_VIDEO);

	// Create a new window for OpenGL rendering prupose
	mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : (0)));
	if (mWindow == 0) {

		printf("Unable to create game application window! %s", SDL_GetError());
		exit(-1);
	}

	mGameTitle = title;

	// Save window properties
	mFullscreen = fullscreen;

	// Place and resize application window
	SDL_GetWindowPosition(mWindow, &mWindowX, &mWindowY);
	SDL_GetWindowSize(mWindow, &mWindowW, &mWindowH);
}

void Game::RegisterEventCallbacks()
{
	RegisterEventCallback(&Game::OnPauseGameEvent);
	RegisterEventCallback(&Game::OnResumeGameEvent);
	RegisterEventCallback(&Game::OnQuitGameEvent);
}

void Game::Init(const char* title, int width, int height, bool fullscreen) {

	// Initialize ECS
	InitializeECS();

	// Initialize SDL
	InitializeSDL(title, width, height, fullscreen);

	// Register Event Callbacks
	RegisterEventCallbacks();

	// Set new app state to initialized
	mAppState = INITIALIZED;

	ECS::ECS_Engine->SendEvent<GameInitializedEvent>();
}

void Game::Terminate() 
{
	if (mAppState == TERMINATED)
		return;

	// set new app state to about to termiante
	mAppState = ABOUT_TO_TERMINATE;

	// Destroy window
	if (mWindow)
		SDL_DestroyWindow(mWindow);

	// Terminate SDL
	SDL_Quit();

	// Terminate ECS
	ECS::Terminate();

	// set new app state to terminated
	mAppState = TERMINATED;
}

void Game::ProcessWindowEvent()
{
	// Pump all SDL events to queue
	SDL_PumpEvents();

	SDL_Event event;
	while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_SYSWMEVENT)) {

		switch (event.window.event) 
		{
			case SDL_QUIT:
				Terminate();
				break;

			case SDL_WINDOWEVENT_SHOWN:
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				break;
			case SDL_WINDOWEVENT_MOVED:
				break;
			case SDL_WINDOWEVENT_RESIZED:
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				break;
			case SDL_WINDOWEVENT_RESTORED:
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
				break;
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

	mFullscreen = !mFullscreen;
	SDL_SetWindowFullscreen(mWindow, mFullscreen);
}

void Game::Pause() {

	// set new app state to paused
	mAppState = PAUSED;
	ECS::ECS_Engine->SendEvent<GamePausedEvent>();
}

void Game::Resume() {

	// set new app state to running
	mAppState = RUNNING;
	ECS::ECS_Engine->SendEvent<GameResumedEvent>();
}

void Game::Run() {

	// set new app state to running
	mAppState = RUNNING;

	ECS::ECS_Engine->SendEvent<GameStartedEvent>();

	while (mAppState < ABOUT_TO_TERMINATE) 
	{
		ProcessWindowEvent();

		ECS::ECS_Engine->Update(DELTA_TIME_STEP);

	}; // MAIN GAME LOOP!
}


void Game::OnPauseGameEvent(const PauseGameEvent* event)
{
	if(this->mAppState == RUNNING)
		this->Pause();
}

void Game::OnResumeGameEvent(const ResumeGameEvent* event)
{
	if (this->mAppState == PAUSED)
		this->Resume();
}

void Game::OnQuitGameEvent(const QuitGameEvent* event)
{
	if (this->mAppState < ABOUT_TO_TERMINATE)
		this->Terminate();
}