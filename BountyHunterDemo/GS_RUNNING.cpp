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


	// update game time time ...
	if (this->m_GameContext.PlayTime > 0.0f)
	{
		this->m_GameContext.PlayTime -= DELTA_TIME_STEP;	
	}
	else
	{
		Player* winner = nullptr;
		for (PlayerId p = 0; p < MAX_PLAYER; ++p)
		{
			Player* player = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>()->GetPlayer(p);
			if (player != nullptr)
			{
				if (winner == nullptr)
				{
					winner = player;
					continue;
				}

				Stash* playerStash = (Stash*)ECS::ECS_Engine->GetEntityManager()->GetEntity(player->GetStash());
				Stash* winnerStash = (Stash*)ECS::ECS_Engine->GetEntityManager()->GetEntity(winner->GetStash());

				if (playerStash->GetStashValue() > winnerStash->GetStashValue())
				{
					winner = player;
				}
			}

		}


		SDL_Log("****************************************");
		SDL_Log("Time is up!\n");
		SDL_Log("%s won the match!", winner->GetPlayerName());
		SDL_Log("****************************************");

		ChangeState(GameState::GAMEOVER);
	}
}

void Game::GS_RUNNING_ENTER()
{
	RegisterEventCallback(&Game::OnCollisionBegin);
	RegisterEventCallback(&Game::OnStashFull);
}

void Game::GS_RUNNING_LEAVE()
{
	UnregisterEventCallback(&Game::OnCollisionBegin);
	UnregisterEventCallback(&Game::OnStashFull);
}