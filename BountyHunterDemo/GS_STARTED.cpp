///-------------------------------------------------------------------------------------------------
/// File:	GS_STARTED.cpp.
///
/// Summary:	Implements the 'STARTED' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

#include "TabletopCamera.h"
#include "Collector.h"
#include "Bounty.h"
#include "PlayerSpawn.h"
#include "BountySpawn.h"
#include "AICollectorController.h"
#include "PlayerCollectorController.h"

void Game::GS_STARTED()
{
	// create test dummies
	WorldSystem* worldSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
	RespawnSystem* respawnSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<RespawnSystem>();
	PlayerSystem* playerSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>();
	
	// spawn max. number of player in a circle also create player spawns
	const float STEP = glm::two_pi<float>() / max(1.0f, (float)MAX_PLAYER);
	const float R = (WORLD_BOUND_MAX[0] - WORLD_BOUND_MIN[0]) * 0.5f;

	for (size_t i = 0; i < MAX_PLAYER; ++i)
	{
		const float angle = i * STEP;
		const float xR = glm::cos(angle) * R;
		const float yR = glm::sin(angle) * R;


		Position spawnPosition(xR, yR, 0.0f);

		Transform initialTransform = glm::translate(glm::mat4(1.0f), spawnPosition) * glm::rotate(angle + glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(2.0f));

		// spawn collector spawn
		GameObjectId collectorSpawn = worldSystem->AddGameObject<PlayerSpawn>(Transform(Position(xR, yR, 1.0f)), spawnPosition, angle + glm::radians(90.0f));

		// spawn collector
		GameObjectId collector = worldSystem->AddGameObject<Collector>(initialTransform, collectorSpawn);

		if ((i == 0) && (HAS_HUMAN_PLAYER == true))
		{
			// Indicate possessed Collector by changing its color
			MaterialComponent* collectorMaterialComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>(collector);
			assert(collectorMaterialComponent != nullptr && "Unable to retrieve collectors material component!");
			collectorMaterialComponent->SetColor(1.0f, 0.0f, 0.0f);

			// create human player
			playerSystem->AddNewPlayer(DEFAULT_PLAYER_NAME, new PlayerCollectorController(collector));
			continue;
		}

		// create ai player
		playerSystem->AddNewPlayer(("Player #" + std::to_string(i)).c_str(), new AICollectorController(collector));
	}

	// create bounty spawn
	const float bountyHalfSpawnSize = R * 0.75f;
	GameObjectId bountySpawn = worldSystem->AddGameObject<BountySpawn>(Transform(Position(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(bountyHalfSpawnSize, bountyHalfSpawnSize, 0.0f)), Position(0.0f, 0.0f, 0.0f), glm::vec2(bountyHalfSpawnSize, bountyHalfSpawnSize), 0.0f);

	// spawn bounty
	for (size_t i = 0; i < MAX_BOUNTY; ++i)
	{
		GameObjectId bounty = worldSystem->AddGameObject<Bounty>(Transform::IDENTITY(), bountySpawn);
		worldSystem->KillGameObject(bounty);
	}


	// create a camera
	GameObjectId cameraId = ECS::ECS_Engine->GetEntityManager()->CreateEntity<TabletopCamera>(glm::vec2(0.0f, 0.0f), -10.0f, 5.0f);
	TabletopCamera* camera = (TabletopCamera*)ECS::ECS_Engine->GetEntityManager()->GetEntity(cameraId);
	camera->SetViewport(0, 0, this->m_WindowWidth, this->m_WindowHeight);

	// put game into game state 'RUNNING'
	ChangeState(GameState::RUNNING);
}

void Game::GS_STARTED_ENTER()
{
	RegisterEventCallback(&Game::OnPauseGame);
	RegisterEventCallback(&Game::OnResumeGame);

	ECS::ECS_Engine->SendEvent<GameStartedEvent>();
}

void Game::GS_STARTED_LEAVE()
{
}