///-------------------------------------------------------------------------------------------------
/// File:	BountyHunterDemo.cpp.
///
/// Summary:	Application entry point.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

Game* g_Application = new Game(GAME_TITLE);

int main(int argc, const char* args[])
{
	// initialize game
	g_Application->Initialize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FULLSCREEN);

	// enter game main-loop
	g_Application->Run();

	delete g_Application;
	g_Application = nullptr;

    return 0;
}

