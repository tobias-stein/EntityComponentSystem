///-------------------------------------------------------------------------------------------------
/// File:	GS_PAUSED.cpp.
///
/// Summary:	Implements the 'PAUSED' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_PAUSED()
{
}

void Game::GS_PAUSED_ENTER()
{
	ECS::ECS_Engine->SendEvent<GamePausedEvent>();
}

void Game::GS_PAUSED_LEAVE()
{
	ECS::ECS_Engine->SendEvent<GameResumedEvent>();
}