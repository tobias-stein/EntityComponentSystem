///-------------------------------------------------------------------------------------------------
/// File:	GS_GAMEOVER.cpp.
///
/// Summary:	Implements the 'GAMEOVER' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_GAMEOVER()
{
}

void Game::GS_GAMEOVER_ENTER()
{
	UnregisterEventCallback(&Game::OnPauseGame);
	UnregisterEventCallback(&Game::OnResumeGame);

	ECS::ECS_Engine->SendEvent<GameoverEvent>();
}

void Game::GS_GAMEOVER_LEAVE()
{
}