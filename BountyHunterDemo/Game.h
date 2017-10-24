///-------------------------------------------------------------------------------------------------
/// File:	Game.h.
///
/// Summary:	The game application class. Manages core initilization stuff, clean-up and main 
/// game loop.
///-------------------------------------------------------------------------------------------------
/// 

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL.h> 

// to prevent:
// Error	LNK2019	unresolved external symbol SDL_main referenced in function main_utf8	BountyHunterDemo	..\EntityComponentSystem\BountyHunterDemo\SDL2main.lib(SDL_windows_main.obj)	1
#undef main 


#include "GameConfiguration.h"
#include "GameEvents.h"
#include "GameTypes.h"

// utility
#include "FPS.h"
#include "SimpleFSM.h"

// game systems
#include "InputSystem.h"
#include "MenuSystem.h"
#include "RenderSystem.h"
#include "WorldSystem.h"
#include "PlayerSystem.h"
#include "LifetimeSystem.h"
#include "RespawnSystem.h"
#include "ControllerSystem.h"
#include "PhysicsSystem.h"
#include "CheatSystem.h"

// game entities
#include "TabletopCamera.h"
#include "Collector.h"
#include "Bounty.h"
#include "CollectorStash.h"
#include "PlayerSpawn.h"
#include "BountySpawn.h"

// player controller
#include "AICollectorController.h"
#include "PlayerCollectorController.h"



class Game : protected ECS::Event::IEventListener, public SimpleFSM {

public:

	///-------------------------------------------------------------------------------------------------
	/// Summary:	Game State Transitions.
	///
	///				+-----------------+
	///				| NOT_INITIALIZED |
	///				+-----------------+
	///				         |
	///				         v
	///				  +-------------+
	///				  | INITIALIZED |
	///				  +-------------+
	///				         |
	///				         v
	///				   +-----------+
	///			  +--->| RESTARTED |<-------------+
	///			  |    +-----------+              |
	///			  |          |                    |
	///			  |          v                    |
	///			  |     +---------+               |
	///			  |     | STARTED |-------------+ |
	///			  |     +---------+             | |
	///			  |          |   ^              v |
	///			  |          |   |         +--------+
	///			  |          |   +---------| PAUSED |
	///			  |          |   |         +--------+
	///			  |          v   v              ^ |
	///			  |     +---------+             | |
	///			  |     | RUNNING |-------------+ |
	///			  |     +---------+               |
	///			  |          |                    |
	///			  |          v                    |
	///			  |    +----------+               |
	///			  +----| GAMEOVER |<--------------+
	///			       +----------+               |
	///			             |                    |
	///			             v                    |
	///			      +------------+              |    
	///			      | TERMINATED |<-------------+
	///			      +------------+
	///-------------------------------------------------------------------------------------------------


	// Define FSM Transition table
	BEGIN_TRANSITION_TABLE

		// Initial State
		TRANSITION_ENTRY(NULL_STATE				, Game::GS_INITIALIZED	, Game::GS_INITIALIZED_ENTER, NO_ONLEAVE_PROC			, GameState::INITIALIZED)

		// Transitions to 'RESTARTED'
		TRANSITION_ENTRY(Game::GS_INITIALIZED	, Game::GS_RESTARTED	, Game::GS_RESTARTED_ENTER	, Game::GS_INITIALIZED_LEAVE, GameState::RESTARTED)
		TRANSITION_ENTRY(Game::GS_PAUSED		, Game::GS_RESTARTED	, Game::GS_RESTARTED_ENTER	, Game::GS_PAUSED_LEAVE		, GameState::RESTARTED)
		TRANSITION_ENTRY(Game::GS_GAMEOVER		, Game::GS_RESTARTED	, Game::GS_RESTARTED_ENTER	, Game::GS_GAMEOVER_LEAVE	, GameState::RESTARTED)

		// Transitions to 'STARTED'
		TRANSITION_ENTRY(Game::GS_RESTARTED		, Game::GS_STARTED		, Game::GS_STARTED_ENTER	, Game::GS_RESTARTED_LEAVE	, GameState::STARTED)
		TRANSITION_ENTRY(Game::GS_PAUSED		, Game::GS_STARTED		, Game::GS_STARTED_ENTER	, Game::GS_PAUSED_LEAVE		, GameState::STARTED)

		// Transitions to 'PAUSED'
		TRANSITION_ENTRY(Game::GS_STARTED		, Game::GS_PAUSED		, Game::GS_PAUSED_ENTER		, Game::GS_STARTED_LEAVE	, GameState::PAUSED)
		TRANSITION_ENTRY(Game::GS_RUNNING		, Game::GS_PAUSED		, Game::GS_PAUSED_ENTER		, Game::GS_RUNNING_LEAVE	, GameState::PAUSED)

		// Transitions to 'RUNNING'
		TRANSITION_ENTRY(Game::GS_STARTED		, Game::GS_RUNNING		, Game::GS_RUNNING_ENTER	, Game::GS_STARTED_LEAVE	, GameState::RUNNING)
		TRANSITION_ENTRY(Game::GS_PAUSED		, Game::GS_RUNNING		, Game::GS_RUNNING_ENTER	, Game::GS_PAUSED_LEAVE		, GameState::RUNNING)

		// Transitions to 'GAMEOVER'
		TRANSITION_ENTRY(Game::GS_RUNNING		, Game::GS_GAMEOVER		, Game::GS_GAMEOVER_ENTER	, Game::GS_RUNNING_LEAVE	, GameState::GAMEOVER)

		// Transitions to 'TERMINATED'
		TRANSITION_ENTRY(Game::GS_GAMEOVER		, Game::GS_TERMINATED	, Game::GS_TERMINATED_ENTER	, Game::GS_GAMEOVER_LEAVE	, GameState::TERMINATED)
		TRANSITION_ENTRY(Game::GS_PAUSED		, Game::GS_TERMINATED	, Game::GS_TERMINATED_ENTER	, Game::GS_PAUSED_LEAVE		, GameState::TERMINATED)

	END_TRANSITION_TABLE


	// FSM State callback functions

	// 'RESTARTED' gamestate
	void GS_INITIALIZED();
	void GS_INITIALIZED_ENTER();
	void GS_INITIALIZED_LEAVE();

	// 'INITIALIZED' gamestate
	void GS_RESTARTED();
	void GS_RESTARTED_ENTER();
	void GS_RESTARTED_LEAVE();

	// 'STARTED' gamestate
	void GS_STARTED();
	void GS_STARTED_ENTER();
	void GS_STARTED_LEAVE();

	// 'PAUSED' gamestate
	void GS_PAUSED();
	void GS_PAUSED_ENTER();
	void GS_PAUSED_LEAVE();

	// 'RUNNING' gamestate
	void GS_RUNNING();
	void GS_RUNNING_ENTER();
	void GS_RUNNING_LEAVE();

	// 'GAMEOVER' gamestate
	void GS_GAMEOVER();
	void GS_GAMEOVER_ENTER();
	void GS_GAMEOVER_LEAVE();

	// 'TERMINATED' gamestate
	void GS_TERMINATED();
	void GS_TERMINATED_ENTER();
	void GS_TERMINATED_LEAVE();

	///-------------------------------------------------------------------------------------------------
	/// EVENT HANDLER
	///-------------------------------------------------------------------------------------------------

	void OnPauseGame(const PauseGameEvent* event);
	void OnResumeGame(const ResumeGameEvent* event);
	void OnRestartGame(const RestartGameEvent* event);
	void OnQuitGame(const QuitGameEvent* event);
	void OnToggleFullscreen(const ToggleFullscreenEvent* event);

	void OnCollisionBegin(const CollisionBeginEvent* event);

	void OnStashFull(const StashFull* event);

private:

	/** mWindow
		The handle to the window instance.
	*/
	SDL_Window*			m_Window;

	
	/** mWindowX
		The horizontal offset of the top-left corner of the applications window.
	*/
	int					m_WindowPosX;

	/** mWindowY
		The vertical offset of the top-left corner of the applications window.
	*/
	int					m_WindowPosY;

	/** mWindowW
		The width of the window.
	*/
	int					m_WindowWidth;

	/** mWindowH
		The height of the window.
	*/
	int					m_WindowHeight;

	/** mFullscreen
		The fullscreen flag is true if the application is running in fullscreen mode.
	*/
	bool				m_Fullscreen;

	/** mGameTitle
		Game Title.
	*/
	const char*			m_GameTitle;

	/// Summary:	A simple frame counter.
	FPS					m_FPS;
	

	/// Summary:	The delta time in seconds.
	float				m_DeltaTime;

	/// Summary:	Context for the game.
	GameContext			m_GameContext;

private:

	void InitializeECS();

	void InitializeSDL();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void Game::ProcessWindowEvent();
	///
	/// Summary:	Process all window event.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	4/10/2017
	///-------------------------------------------------------------------------------------------------

	void ProcessWindowEvent();

	void Terminate();

public:

	/** C'tor
	*/
	Game(const char* name = "Game Name");

	/** D'tor
	*/
	~Game();

	/** Init
		The init method will conatin all code that will initialize the new game application
		instance.
	*/
	void Initialize(int width, int height, bool fullscreen = false);

	/** Run
		Kicks off the main game loop.
	*/
	void Run();

	/** ToggleFullscreen
		The togggle fullscreen method will change the application from running in fullscreen to
		window mode and vice versa.
	*/
	void ToggleFullscreen();



	inline SDL_Window*	GetWindow()				const { return this->m_Window; }

	inline bool			IsFullscreenMode()		const { return m_Fullscreen; }

	inline GameState	GetActiveGameState()	const { return (GameState)this->GetActiveState(); }
	inline bool			IsInitialized()			const { return (this->GetActiveState() >  GameState::INITIALIZED); }
	inline bool			IsRestarted()			const { return (this->GetActiveState() == GameState::RESTARTED); }
	inline bool			IsStarted()				const { return (this->GetActiveState() == GameState::STARTED); }
	inline bool			IsPaused()				const { return (this->GetActiveState() == GameState::PAUSED); }
	inline bool			IsRunning()				const { return (this->GetActiveState() == GameState::RUNNING); }
	inline bool			IsGameOver()			const { return (this->GetActiveState() == GameState::GAMEOVER); }
	inline bool			IsTerminated()			const { return (this->GetActiveState() == GameState::TERMINATED); }

	

}; // class GameApp

// global game instance, created in 'BountyHunterDemo.cpp'
extern Game* g_GameInstance;

#endif // __APPLICATION_H__