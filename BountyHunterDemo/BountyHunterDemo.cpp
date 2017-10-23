///-------------------------------------------------------------------------------------------------
/// File:	BountyHunterDemo.cpp.
///
/// Summary:	Application entry point.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

Game* g_GameInstance = new Game(GAME_TITLE);

int main(int argc, const char* args[])
{
	// initialize game
	g_GameInstance->Initialize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_WINDOW_FULLSCREEN);

	// enter game main-loop
	g_GameInstance->Run();

	delete g_GameInstance;
	g_GameInstance = nullptr;

    return 0;
}

