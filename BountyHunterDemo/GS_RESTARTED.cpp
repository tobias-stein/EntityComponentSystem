///-------------------------------------------------------------------------------------------------
/// File:	GS_RESTARTED.cpp.
///
/// Summary:	Implements the 'RESTARTED' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_RESTARTED()
{
	// put game into game state 'STARTED'
	ChangeState(GameState::STARTED);
}

void Game::GS_RESTARTED_ENTER()
{
}

void Game::GS_RESTARTED_LEAVE()
{
}