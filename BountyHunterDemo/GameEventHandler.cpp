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

void Game::OnRestartGame(const RestartGameEvent * event)
{
	if (this->IsPaused() == true)
		PopState(false); // prevent state stack from filling up

	this->ChangeState(GameState::RESTARTED);
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
	{
		if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
		{
			// kill collector
			WorldSystem* WS = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
			WS->KillGameObject(event->objectA);
			WS->KillGameObject(event->objectB);

			// reset collected bounty to zero
			((Collector*)objectA)->ResetCollectedBounty();
			((Collector*)objectB)->ResetCollectedBounty();
		}
	}


	// If collector collided with bounty, increase player bounty ...
	{
		static const auto CollectBountyAction = [&](Collector* collector, Bounty* bounty)
		{
			// Kill the bounty object
			WorldSystem* WS = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
			WS->KillGameObject(bounty->GetEntityID());

			// increase collector's bounty
			collector->CollectBounty(bounty->GetBounty());
		};

		if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Bounty::STATIC_ENTITY_TYPE_ID))
		{
			// note: ai controlled collector entities use an additional collision shape (a sensor)
			// to get notified when bounty is in range. This sensor-shape also will trigger this 
			// collision check, so we need to check if the collision categories are not of type
			// radar here...
			if(event->details.collisionCategoryA == CollisionCategory::Player_Category)
				CollectBountyAction((Collector*)objectA, (Bounty*)objectB);
		}
		else if ((typeA == Bounty::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
		{
			// note: see above.
			if (event->details.collisionCategoryB == CollisionCategory::Player_Category)
				CollectBountyAction((Collector*)objectB, (Bounty*)objectA);
		}
	}


	// If collector collided with player's stash ...
	{
		static const auto StashBountyAction = [](Collector* collector, Stash* stash)
		{
			// make sure we stash bounty in correct stash
			//if (collector->GetPlayer() != stash->GetOwner())
			//	return;

			// do stash bounty
			stash->StashBounty(collector->GetCollectedBounty());
			collector->ResetCollectedBounty();
		};

		if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Stash::STATIC_ENTITY_TYPE_ID))
		{
			StashBountyAction((Collector*)objectA, (Stash*)objectB);
		}
		else if ((typeA == Stash::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
		{
			StashBountyAction((Collector*)objectB, (Stash*)objectA);
		}
	}

	// If collector collided with wall ...
	{
		static const auto WallCollisionAction = [](Collector* collector, Wall* wall)
		{
			auto collTC = collector->GetComponent<TransformComponent>();
			auto wallTC = wall->GetComponent<TransformComponent>();

			auto collPos = collTC->GetPosition();
			auto wallNrm = wallTC->GetRight();
			
			auto newPos = Position(collPos);
			
			if ((glm::abs(wallNrm.x) > 0.005f) == true)
			{
				newPos.x *= -0.95f;
			}

			if ((glm::abs(wallNrm.y) > 0.005f) == true)
			{
				newPos.y *= -0.95f;
			}

			collTC->SetPosition(newPos);
			collector->GetComponent<RigidbodyComponent>()->SetTransform(*collTC);			
		};

		if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Wall::STATIC_ENTITY_TYPE_ID))
		{
			WallCollisionAction((Collector*)objectA, (Wall*)objectB);
		}
		else if ((typeA == Wall::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
		{
			WallCollisionAction((Collector*)objectB, (Wall*)objectA);
		}
	}
}

void Game::OnStashFull(const StashFull* event)
{
	Stash* stash = (Stash*)ECS::ECS_Engine->GetEntityManager()->GetEntity(event->stashId);
	if (stash->GetStashValue() >= PLAYER_STASH_SIZE)
	{
		Player* player = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>()->GetPlayer(stash->GetOwner());

		SDL_Log("****************************************");
		SDL_Log("Stash is full!\n");
		SDL_Log("%s won the match!", player->GetPlayerName());
		SDL_Log("****************************************");

		ChangeState(GameState::GAMEOVER);
	}
}
