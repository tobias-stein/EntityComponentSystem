///-------------------------------------------------------------------------------------------------
/// File:	Game.cpp.
///
/// Summary:	Implements the game application class.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

#include <ECS.h>

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

void Game::Init( const char* title, int width, int height, bool fullscreen ) {

	// Initialize ECS
	ECS::Initialize();

	// Initialize SDL 2.0
	SDL_Init(SDL_INIT_VIDEO);

	// Create a new window for OpenGL rendering prupose
	mWindow = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : (0)));	
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

	// Set new app state to initialized
	mAppState = INITIALIZED;
}

void Game::Terminate() 
{
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

void Game::Update( const float dt ) {


	// Poll all pending SDL events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		switch (e.type) {

			case SDL_WINDOWEVENT_RESIZED: {

				mWindowW = e.window.data1;
				mWindowH = e.window.data2;

				//Resize( mWindowW, mWindowH );	
				break;
			}

			case SDL_WINDOWEVENT_MOVED: {

				mWindowY = e.window.data1;
				mWindowX = e.window.data2;
				break;
			}
 
			case SDL_MOUSEBUTTONDOWN: {

				/* let a special function handle the mouse button down event */
				switch ( e.button.button ) {
					case SDL_BUTTON_LEFT:
						break;

					case SDL_BUTTON_MIDDLE:
						break;
					case SDL_BUTTON_RIGHT:
						break;					
				}
				break;
			}

			/* mouse up handler */
			case SDL_MOUSEBUTTONUP: {

		
				/* let a special function handle the mouse button up event */
				switch ( e.button.button ) {

					case SDL_BUTTON_LEFT:
						//TwMouseButton( TwMouseAction::TW_MOUSE_RELEASED, TwMouseButtonID::TW_MOUSE_LEFT);
						break;
					case SDL_BUTTON_MIDDLE:
						break;
					case SDL_BUTTON_RIGHT:
						break;
				}
				break;
			}


			case ::SDL_MOUSEWHEEL: {

				break;
			}

			/* key down */
			case SDL_KEYDOWN: {

				switch(e.key.keysym.scancode) {

					case SDL_SCANCODE_ESCAPE: {

						mAppState = ABOUT_TO_TERMINATE;
						break;
					}
				}

				break;
			}
 
			/* key up */
			case SDL_KEYUP: {

				break;
			}
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
}

void Game::Resume() {

	// set new app state to running
	mAppState = RUNNING;
}

void Game::Run() {

	// set new app state to running
	mAppState = RUNNING;

	while (mAppState < ABOUT_TO_TERMINATE) 
	{
		Update(DELTA_TIME_STEP);

	}; // MAIN GAME LOOP!
}
