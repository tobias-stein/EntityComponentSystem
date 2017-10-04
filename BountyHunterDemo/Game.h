///-------------------------------------------------------------------------------------------------
/// File:	Game.h.
///
/// Summary:	The game application class. Manages core initilization stuff, clean-up and main 
/// game loop.
///-------------------------------------------------------------------------------------------------
/// 

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "GameConfiguration.h"
#include "GameEvents.h"

#include <stdio.h>

#include <SDL.h> 

#include <ECS.h>

// to prevent:
// Error	LNK2019	unresolved external symbol SDL_main referenced in function main_utf8	BountyHunterDemo	..\EntityComponentSystem\BountyHunterDemo\SDL2main.lib(SDL_windows_main.obj)	1
#undef main 

class Game : public ECS::Event::IEventListener {

public:


	enum State {

		NOT_INITIALIZED = 0,
		INITIALIZED,
		RUNNING,
		PAUSED,
		ABOUT_TO_TERMINATE,
		TERMINATED
	}; // enum State

private:

	/** mWindow
		The handle to the window instance.
	*/
	SDL_Window*			mWindow;

	
	/** mWindowX
		The horizontal offset of the top-left corner of the applications window.
	*/
	int					mWindowX;

	/** mWindowY
		The vertical offset of the top-left corner of the applications window.
	*/
	int					mWindowY;

	/** mWindowW
		The width of the window.
	*/
	int					mWindowW;

	/** mWindowH
		The height of the window.
	*/
	int					mWindowH;

	/** mFullscreen
		The fullscreen flag is true if the application is running in fullscreen mode.
	*/
	bool				mFullscreen;

	/** mGameTitle
		Game Title.
	*/
	const char*			mGameTitle;

	/** mAppState
		Indicates the current state the game application is in.
	*/
	State				mAppState;


private:

	void InitializeECS();

	void InitializeSDL(const char* title, int width, int height, bool fullscreen);

	void RegisterEventCallbacks();

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


	void OnPauseGameEvent(const PauseGameEvent* event);
	void OnResumeGameEvent(const ResumeGameEvent* event);
	void OnQuitGameEvent(const QuitGameEvent* event);

public:

	/** C'tor
	*/
	Game();

	/** D'tor
	*/
	~Game();

	/** Init
		The init method will conatin all code that will initialize the new game application
		instance.
	*/
	void Init( const char* title, int width, int height, bool fullscreen = false );

	/** Run
		Kicks off the main game loop.
	*/
	void Run();
	
	/** Pause
		Pause the current running game and stop the game time.
	*/
	void Pause();

	/** Resume
		Resumes the current paused game and the game time.
	*/
	void Resume();

	/** Terminate
		The termine method will shutdown the game and terminate the application.
	*/
	void Terminate();

	/** ToggleFullscreen
		The togggle fullscreen method will change the application from running in fullscreen to
		window mode and vice versa.
	*/
	void ToggleFullscreen();




	inline bool	IsFullscreenMode()	const { return mFullscreen; }

	inline bool IsInitialized()		const { return (mAppState >  NOT_INITIALIZED); }
	inline bool IsTerminated()		const { return (mAppState >= ABOUT_TO_TERMINATE); }
	inline bool IsPaused()			const { return (mAppState == PAUSED); }
	inline bool IsRunning()			const { return (mAppState == RUNNING); }

	inline SDL_Window* GetWindow()	const { return this->mWindow; }

}; // class GameApp

#endif // __APPLICATION_H__