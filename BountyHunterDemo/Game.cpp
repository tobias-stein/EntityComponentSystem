///-------------------------------------------------------------------------------------------------
/// File:	Game.cpp.
///
/// Summary:	Implements the game application class.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

#include "InputSystem.h"
#include "MenuSystem.h"
#include "RenderSystem.h"
#include "WorldSystem.h"
#include "RespawnSystem.h"

Game::Game() :
	mAppState(NOT_INITIALIZED),
	mWindow(nullptr),
	mFullscreen(false),
	mWindowX(-1), mWindowY(-1),
	mWindowW(-1), mWindowH(-1)
{}

Game::~Game()
{}


void Game::InitializeECS()
{
	// start the engine
	ECS::Initialize();


	// Create and initialize systems

	// InputSystem
	InputSystem* IS = ECS::ECS_Engine->GetSystemManager()->AddSystem<InputSystem>();
	ECS::ECS_Engine->GetSystemManager()->SetSystemPriority<InputSystem>(ECS::HIGH_SYSTEM_PRIORITY);

	// MenuSystem
	MenuSystem* MS = ECS::ECS_Engine->GetSystemManager()->AddSystem<MenuSystem>();

	// RenderSystem
	RenderSystem* RS = ECS::ECS_Engine->GetSystemManager()->AddSystem<RenderSystem>(this->mWindow);

	// WorldSystem
	IWorld* world = new World2D(Bounds2D(Point2D(WORLD_BOUND_MIN[0], WORLD_BOUND_MIN[1]), Point2D(WORLD_BOUND_MAX[0], WORLD_BOUND_MAX[1])), glm::vec2(WORLD_UP_VECTOR[0], WORLD_UP_VECTOR[1]));
	WorldSystem* WS = ECS::ECS_Engine->GetSystemManager()->AddSystem<WorldSystem>(world);

	RespawnSystem* RSS = ECS::ECS_Engine->GetSystemManager()->AddSystem<RespawnSystem>();

	// Add system dependencies
}

void Game::InitializeSDL(const char* title, int width, int height, bool fullscreen)
{
	// Initialize SDL 2.0
	SDL_Init(SDL_INIT_VIDEO);

	// Create a new window for OpenGL rendering prupose
	mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : (0)));
	if (mWindow == 0) {

		SDL_Log("Unable to create game application window! %s", SDL_GetError());
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
	RegisterEventCallback(&Game::OnToggleFullscreenEvent);
}

void Game::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&Game::OnPauseGameEvent);
	UnregisterEventCallback(&Game::OnResumeGameEvent);
	UnregisterEventCallback(&Game::OnQuitGameEvent);
	UnregisterEventCallback(&Game::OnToggleFullscreenEvent);
}

void Game::Init(const char* title, int width, int height, bool fullscreen) {

	// Initialize SDL
	InitializeSDL(title, width, height, fullscreen);

	// Initialize ECS
	InitializeECS();

	// broadcast initial window state
	ECS::ECS_Engine->SendEvent<WindowResizedEvent>(width, height);

	if (fullscreen == false)
		ECS::ECS_Engine->SendEvent<EnterFullscreenModeEvent>();
	else
		ECS::ECS_Engine->SendEvent<EnterWindowModeEvent>();


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

	// note: we need to release Game event callbacks before termination ECS or we might risk an exception due 
	// enforcement of event callback unregistration through IEventListener d'tor
	UnregisterEventCallbacks();

	// Terminate ECS
	ECS::Terminate();

	// Destroy window
	if (mWindow)
		SDL_DestroyWindow(mWindow);

	// Terminate SDL
	SDL_Quit();	

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
				OnQuitGameEvent(nullptr);
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

	if(mFullscreen == false)
		ECS::ECS_Engine->SendEvent<EnterFullscreenModeEvent>();
	else
		ECS::ECS_Engine->SendEvent<EnterWindowModeEvent>();

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

#include "TabletopCamera.h"
#include "Collector.h"
#include "Bounty.h"
#include "PlayerSpawn.h"
#include "BountySpawn.h"


void Game::Run()
{

	// set new app state to running
	mAppState = RUNNING;

	ECS::ECS_Engine->SendEvent<GameStartedEvent>();

	// create test dummies
	WorldSystem* worldSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
	RespawnSystem* respawnSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<RespawnSystem>();

	// spawn max. number of player in a circle also create player spawns
	const float STEP = glm::two_pi<float>() / max(1.0f, (float)MAX_PLAYER);
	const float R = (WORLD_BOUND_MAX[0] - WORLD_BOUND_MIN[0]) * 0.5f;

	for (size_t i = 0; i < MAX_PLAYER; ++i)
	{
		const float angle = i * STEP;
		const float xR = glm::cos(angle) * R;
		const float yR = glm::sin(angle) * R;


		Position spawnPosition(xR, yR, 0.0f);

		Transform initialTransform = glm::translate(glm::mat4(1.0f), spawnPosition) * glm::rotate(angle + glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		
		// spawn player spawn
		GameObjectId playerSpawn = worldSystem->AddGameObject<PlayerSpawn>(Transform(Position(xR, yR, 1.0f)), spawnPosition, angle + glm::radians(90.0f));

		// spawn player
		worldSystem->AddGameObject<Collector>(initialTransform, playerSpawn);	
	}
	
	// create bounty spawn
	const float bountyHalfSpawnSize = R * 0.9f;
	GameObjectId bountySpawn = worldSystem->AddGameObject<BountySpawn>(Transform(Position(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(bountyHalfSpawnSize, bountyHalfSpawnSize, 0.0f)), Position(0.0f, 0.0f, 0.0f), glm::vec2(bountyHalfSpawnSize, bountyHalfSpawnSize), 0.0f);
	
	// spawn bounty
	for (size_t i = 0; i < MAX_BOUNTY; ++i)
	{
		GameObjectId bounty = worldSystem->AddGameObject<Bounty>(Transform::IDENTITY(), bountySpawn);
		worldSystem->KillGameObject(bounty);
	}

	// create a camera
	ECS::ECS_Engine->GetEntityManager()->CreateEntity<TabletopCamera>(glm::vec2(0.0f, 0.0f), -10.0f, 5.0f);

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
		this->mAppState = ABOUT_TO_TERMINATE;
}

void Game::OnToggleFullscreenEvent(const ToggleFullscreenEvent* event)
{
	this->ToggleFullscreen();
}