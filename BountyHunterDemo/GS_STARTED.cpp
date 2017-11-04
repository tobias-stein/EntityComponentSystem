///-------------------------------------------------------------------------------------------------
/// File:	GS_STARTED.cpp.
///
/// Summary:	Implements the 'STARTED' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_STARTED()
{
	WorldSystem* worldSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
	RespawnSystem* respawnSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<RespawnSystem>();
	PlayerSystem* playerSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>();

	//------------------------------------------
	// Create Camera
	//------------------------------------------
	
	GameObjectId cameraId = ECS::ECS_Engine->GetEntityManager()->CreateEntity<TabletopCamera>(glm::vec2(0.0f, 0.0f), -10.0f, 5.0f);
	TabletopCamera* camera = (TabletopCamera*)ECS::ECS_Engine->GetEntityManager()->GetEntity(cameraId);
	camera->SetViewport(0, 0, this->m_WindowWidth, this->m_WindowHeight);


	//------------------------------------------
	// Create Walls
	//------------------------------------------

	glm::vec3 wallSize = glm::vec3(1.0f, WORLD_BOUND_MAX[1] + 3.0f, 1.0f);

	// left
	worldSystem->AddGameObject<Wall>(Transform(Position(WORLD_BOUND_MIN[0] - 3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(0.0f), wallSize), wallSize);

	// right
	worldSystem->AddGameObject<Wall>(Transform(Position(WORLD_BOUND_MAX[0] + 3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(180.0f), wallSize), wallSize);

	// top
	worldSystem->AddGameObject<Wall>(Transform(Position(0.0f, WORLD_BOUND_MAX[0] + 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(90.0f), wallSize), wallSize); 

	// bottom
	worldSystem->AddGameObject<Wall>(Transform(Position(0.0f, WORLD_BOUND_MIN[0] - 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(270.0f), wallSize), wallSize);


	//------------------------------------------
	// Create Player
	//------------------------------------------
 
	const float STEP = glm::two_pi<float>() / max(1.0f, (float)MAX_PLAYER);
	const float R = (WORLD_BOUND_MAX[0] - WORLD_BOUND_MIN[0]) * 0.5f;

	for (size_t i = 0; i < MAX_PLAYER; ++i)
	{
		const float angle = i * STEP;
		const float xR = glm::cos(angle) * R;
		const float yR = glm::sin(angle) * R;


		Position spawnPosition(xR, yR, 0.0f);

		Transform initialTransform = glm::translate(glm::mat4(1.0f), spawnPosition) * glm::rotate(angle + glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(2.0f));

		// create collector spawn
		GameObjectId collectorSpawn = worldSystem->AddGameObject<PlayerSpawn>(Transform(Position(xR, yR, 1.0f)), spawnPosition, angle + glm::radians(90.0f));


		PlayerId playerId = INVALID_PLAYER_ID;
		Player* player = nullptr;
		if ((i == 0) && (HAS_HUMAN_PLAYER == true))
		{
			// create human player
			playerId = playerSystem->AddNewPlayer(DEFAULT_PLAYER_NAME);

			// create stash and collector
			GameObjectId playerStashId = worldSystem->AddGameObject<Stash>(glm::translate(glm::mat4(1.0f), Position(xR, yR, 1.0f)) * glm::scale(glm::vec3(2.5f)), playerId);
			GameObjectId collectorId = worldSystem->AddGameObject<Collector>(initialTransform, collectorSpawn);

			player = playerSystem->GetPlayer(playerId);
			player->SetStash(playerStashId);
			player->SetController(new PlayerCollectorController(collectorId, playerId));
		}
		else
		{
			// create ai player
			playerId = playerSystem->AddNewPlayer(("Player #" + std::to_string(i)).c_str());

			// create stash and collector
			GameObjectId playerStashId = worldSystem->AddGameObject<Stash>(glm::translate(glm::mat4(1.0f), Position(xR, yR, 1.0f)) * glm::scale(glm::vec3(2.5f)), playerId);
			GameObjectId collectorId = worldSystem->AddGameObject<Collector>(initialTransform, collectorSpawn);

			player = playerSystem->GetPlayer(playerId);
			player->SetStash(playerStashId);
			player->SetController(new AICollectorController(collectorId, playerId, AICollectorControllerDesc()));
		}
	}


	//------------------------------------------
	// Create Bounty
	//------------------------------------------

	// create bounty spawn
	const float bountyHalfSpawnSize = R * 0.75f;
	GameObjectId bountySpawnId = worldSystem->AddGameObject<BountySpawn>(Transform(Position(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(bountyHalfSpawnSize, bountyHalfSpawnSize, 0.0f)), Position(0.0f, 0.0f, 0.0f), glm::vec2(bountyHalfSpawnSize, bountyHalfSpawnSize), 0.0f);
	BountySpawn* bountySpawn = (BountySpawn*)ECS::ECS_Engine->GetEntityManager()->GetEntity(bountySpawnId);

	// spawn bounty
	for (size_t i = 0; i < MAX_BOUNTY; ++i)
	{
		SpawnInfo spawnInfo = bountySpawn->GetSpawnInfo();
		GameObjectId bountyId = worldSystem->AddGameObject<Bounty>(Transform(spawnInfo.m_SpawnPosition, glm::vec3(0.0f, 0.0f, 1.0f), spawnInfo.m_SpawnOrientation.z), bountySpawnId);
		((Bounty*)ECS::ECS_Engine->GetEntityManager()->GetEntity(bountyId))->OnEnable(); // little hack to get the initial bounty size, color and value
	}

	// put game into game state 'RUNNING'
	ChangeState(GameState::RUNNING);
}

void Game::GS_STARTED_ENTER()
{
	RegisterEventCallback(&Game::OnPauseGame);
	RegisterEventCallback(&Game::OnResumeGame);	
}

void Game::GS_STARTED_LEAVE()
{
}