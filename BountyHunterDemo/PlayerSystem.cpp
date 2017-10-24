///-------------------------------------------------------------------------------------------------
/// File:	PlayerSystem.cpp.
///
/// Summary:	Implements the player system class.
///-------------------------------------------------------------------------------------------------

#include "PlayerSystem.h"
#include "ControllerSystem.h"

PlayerSystem::PlayerSystem() :
	m_Players(MAX_PLAYER, nullptr)
{}

PlayerSystem::~PlayerSystem()
{
	for (PlayerId i = 0; i < this->m_Players.size(); ++i)
	{
		if (this->m_Players[i] != nullptr)
		{
			delete this->m_Players[i];
			this->m_Players[i] = nullptr;
		}
	}
}

PlayerId PlayerSystem::AddNewPlayer(const char* playerName, const Controller& controller)
{
	for (PlayerId i = 0; i < this->m_Players.size(); ++i)
	{
		if (this->m_Players[i] == nullptr)
		{
			this->m_Players[i] = new Player(i, playerName, controller);

			ECS::ECS_Engine->SendEvent<PlayerJoined>(i);
			ECS::ECS_Engine->GetSystemManager()->GetSystem<ControllerSystem>()->RegisterController(&this->m_Players[i]->GetController());
			return i;
		}
	}

	return INVALID_PLAYER_ID;
}

void PlayerSystem::RemovePlayer(PlayerId playerId)
{
	assert(playerId < MAX_PLAYER && "Invalid player id!");

	if (this->m_Players[playerId] != nullptr)
	{
		ECS::ECS_Engine->GetSystemManager()->GetSystem<ControllerSystem>()->UnregisterController(&this->m_Players[playerId]->GetController());
		delete this->m_Players[playerId];
		this->m_Players[playerId] = nullptr;

		ECS::ECS_Engine->SendEvent<PlayerLeft>(playerId);
	}
}

void PlayerSystem::RemoveAllPlayers()
{
	for (PlayerId i = 0; i < this->m_Players.size(); ++i)
	{
		if (this->m_Players[i] != nullptr)
		{
			ECS::ECS_Engine->GetSystemManager()->GetSystem<ControllerSystem>()->UnregisterController(&this->m_Players[i]->GetController());
			delete this->m_Players[i];
			this->m_Players[i] = nullptr;

			ECS::ECS_Engine->SendEvent<PlayerLeft>(i);
		}
	}
}
