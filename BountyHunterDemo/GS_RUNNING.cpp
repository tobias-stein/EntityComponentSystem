///-------------------------------------------------------------------------------------------------
/// File:	GS_RUNNING.cpp.
///
/// Summary:	Implements the 'RUNNING' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_RUNNING()
{
	// if there is freeze time ...
	if (this->m_GameContext.FreezeTime > 0.0f)
	{
		this->m_GameContext.FreezeTime -= DELTA_TIME_STEP;
		return;
	}
}

void Game::GS_RUNNING_ENTER()
{
	RegisterEventCallback(&Game::OnCollisionBegin);
}

void Game::GS_RUNNING_LEAVE()
{
	UnregisterEventCallback(&Game::OnCollisionBegin);
}