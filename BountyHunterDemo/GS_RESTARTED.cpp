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
	UnregisterEventCallback(&Game::OnPauseGame);
	UnregisterEventCallback(&Game::OnResumeGame);

	ECS::ECS_Engine->SendEvent<GameRestartedEvent>();
}

void Game::GS_RESTARTED_LEAVE()
{
}