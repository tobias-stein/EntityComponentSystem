#include "RespawnSystem.h"
#include "WorldSystem.h"

RespawnSystem::RespawnSystem() :
	m_Spawns(1024, INVALID_GAMEOBJECT_ID)
{
	RegisterEventCallbacks();
}

RespawnSystem::~RespawnSystem()
{
	UnregisterEventCallbacks();
}

void RespawnSystem::Update(float dt)
{
	auto s = this->m_RespawnQueue.begin();
	while (s != this->m_RespawnQueue.end())
	{
		s->m_RemainingDeathTime -= dt;
		if (s->m_RemainingDeathTime <= 0.0f)
		{
			SpawnInfo spawnInfo(INVALID_POSITION, glm::vec3(0.0f));

			// if spawnable is not bound to a fix spawn ...
			if (s->m_spawnID == INVALID_GAMEOBJECT_ID)
			{
				// ... spawn game object at pre-set position
				if (s->m_RespawnPosition != INVALID_POSITION)
				{
					spawnInfo.m_SpawnPosition = s->m_RespawnPosition;
					spawnInfo.m_SpawnOrientation = s->m_RespawnOrientation;
				}
				// ... spawn game object at randowm location in the world
				else
				{
					spawnInfo.m_SpawnPosition = Position(glm::linearRand(glm::vec3(WORLD_BOUND_MIN[0], WORLD_BOUND_MIN[0], 0.0f), glm::vec3(WORLD_BOUND_MAX[0], WORLD_BOUND_MAX[0], 0.0f)));
				}
			}
			// use spawn's SpawnInfo to spawn game object
			else
			{
				for (auto S : this->m_Spawns)
				{
					if (S == s->m_spawnID)
					{
						GameObjectSpawn* spawn = (GameObjectSpawn*)ECS::ECS_Engine->GetEntityManager()->GetEntity(S);	
						assert(spawn->IsActive() && "Failure! Trying to spawn a game object on a disabled spawn!");

						spawnInfo = spawn->GetSpawnInfo();
						break;
					}
				}
			}

			assert(spawnInfo.m_SpawnPosition != INVALID_POSITION && "Failed to respawn game object!");
			
			// maintain old game object scale
			glm::vec3 oldScale = ECS::ECS_Engine->GetComponentManager()->GetComponent<TransformComponent>(s->m_spawnableID)->GetScale();

			Transform transform = glm::translate(glm::mat4(1.0f), spawnInfo.m_SpawnPosition) * glm::yawPitchRoll(spawnInfo.m_SpawnOrientation[0], spawnInfo.m_SpawnOrientation[1], spawnInfo.m_SpawnOrientation[2]) * glm::scale(oldScale);

			// spawn object
			ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>()->SpawnGameObject(s->m_spawnableID, transform);

			// remove from queue
			this->m_RespawnQueue.erase(s++);
		}
		else
		{
			++s;
		}
	}
}

void RespawnSystem::RespawnGameObject(const GameObjectId gameObjectId)
{
	// check if entity has respawn ability
	RespawnComponent* entityRespawnComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<RespawnComponent>(gameObjectId);
	assert((entityRespawnComponent != nullptr && entityRespawnComponent->IsActive()) && "Cannot respawn game object, it has no RespawnComponent attached!");

	this->DoRespawn(gameObjectId, entityRespawnComponent);
}

void RespawnSystem::Reset()
{
	this->m_RespawnQueue.clear();
}

void RespawnSystem::DoRespawn(const GameObjectId gameObjectId, RespawnComponent* entityRespawnComponent)
{
	// add to queue
	for (auto it = this->m_RespawnQueue.begin(); it != this->m_RespawnQueue.end(); ++it)
	{
		if (it->m_RemainingDeathTime > entityRespawnComponent->m_RespawnTime)
		{
			if (entityRespawnComponent->m_SpawnId != INVALID_GAMEOBJECT_ID)
				this->m_RespawnQueue.insert(it, PendingRespawn(gameObjectId, entityRespawnComponent->m_SpawnId, entityRespawnComponent->m_RespawnTime));
			else
				this->m_RespawnQueue.insert(it, PendingRespawn(gameObjectId, entityRespawnComponent->m_RespawnTime, entityRespawnComponent->m_RespawnPosition, entityRespawnComponent->m_RespawnOrientation));
		}
	}

	if (entityRespawnComponent->m_SpawnId != INVALID_GAMEOBJECT_ID)
		this->m_RespawnQueue.push_back(PendingRespawn(gameObjectId, entityRespawnComponent->m_SpawnId, entityRespawnComponent->m_RespawnTime));
	else
		this->m_RespawnQueue.push_back(PendingRespawn(gameObjectId, entityRespawnComponent->m_RespawnTime, entityRespawnComponent->m_RespawnPosition, entityRespawnComponent->m_RespawnOrientation));
}

void RespawnSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&RespawnSystem::OnGameObjectCreated);
	RegisterEventCallback(&RespawnSystem::OnGameObjectDestroyed);
	RegisterEventCallback(&RespawnSystem::OnGameObjectKilled);
}

void RespawnSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&RespawnSystem::OnGameObjectCreated);
	UnregisterEventCallback(&RespawnSystem::OnGameObjectDestroyed);
	UnregisterEventCallback(&RespawnSystem::OnGameObjectKilled);
}

void RespawnSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
	if (event->m_EntityTypeID != GameObjectSpawn::STATIC_ENTITY_TYPE_ID)
		return;

	for (size_t i = 0; i < this->m_Spawns.size(); ++i)
	{
		if (this->m_Spawns[i] == INVALID_GAMEOBJECT_ID)
		{
			this->m_Spawns[i] = event->m_EntityID;
			return;
		}
	}

	this->m_Spawns.push_back(event->m_EntityID);
}

void RespawnSystem::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
	if (event->m_EntityTypeID != GameObjectSpawn::STATIC_ENTITY_TYPE_ID)
		return;

	for (size_t i = 0; i < this->m_Spawns.size(); ++i)
	{
		if (this->m_Spawns[i] == event->m_EntityID)
		{
			this->m_Spawns[i] = INVALID_GAMEOBJECT_ID;
			return;
		}
	}
}

void RespawnSystem::OnGameObjectKilled(const GameObjectKilled * event)
{
	// check if entity has respawn ability
	RespawnComponent* entityRespawnComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<RespawnComponent>(event->m_EntityID);

	if (entityRespawnComponent == nullptr || (entityRespawnComponent->IsActive() == false) || (entityRespawnComponent->m_AutoRespawn == false))
		return;

	this->DoRespawn(event->m_EntityID, entityRespawnComponent);
}
