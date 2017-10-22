///-------------------------------------------------------------------------------------------------
/// File:	GS_TERMINATED.cpp.
///
/// Summary:	Implements the 'GAMEOVER' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_TERMINATED()
{
}

void Game::GS_TERMINATED_ENTER()
{
	this->Terminate();
}

void Game::GS_TERMINATED_LEAVE()
{
}