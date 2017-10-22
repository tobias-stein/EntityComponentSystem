///-------------------------------------------------------------------------------------------------
/// File:	GameEventHandler.cpp.
///
/// Summary:	Implements the game event handler class.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::OnPauseGame(const PauseGameEvent* event)
{
	this->PushState(GameState::PAUSED);
}

void Game::OnResumeGame(const ResumeGameEvent* event)
{
	this->PopState();
}

void Game::OnQuitGame(const QuitGameEvent* event)
{
	this->ChangeState(GameState::TERMINATED);
}

void Game::OnToggleFullscreen(const ToggleFullscreenEvent* event)
{
	this->ToggleFullscreen();
}

void Game::OnCollisionBegin(const CollisionBeginEvent* event)
{
	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	// If collector collided with collector, kill 'em both ...
	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		// kill collector
		WorldSystem* WS = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
		WS->KillGameObject(event->objectA);
		WS->KillGameObject(event->objectB);

		// reset collected player bounty to zero
		PlayerSystem* PS = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>();
		Player* playerA = PS->GetPlayer(((Collector*)objectA)->GetPlayer());
		Player* playerB = PS->GetPlayer(((Collector*)objectB)->GetPlayer());

		playerA->ResetCollectedBounty();
		playerB->ResetCollectedBounty();
	}

	// If collector collided with bounty, increase player bounty ...
	static const auto CollectBountyAction = [](Collector* collector, Bounty* bounty)
	{
		// Kill the bounty object
		WorldSystem* WS = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
		WS->KillGameObject(bounty->GetEntityID());

		// increase player's bounty
		PlayerSystem* PS = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>();
		PS->GetPlayer(collector->GetPlayer())->CollectBounty(bounty->GetBounty());
	};

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Bounty::STATIC_ENTITY_TYPE_ID))
	{
		CollectBountyAction((Collector*)objectA, (Bounty*)objectB);
	}
	else if ((typeA == Bounty::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		CollectBountyAction((Collector*)objectB, (Bounty*)objectA);
	}
}
