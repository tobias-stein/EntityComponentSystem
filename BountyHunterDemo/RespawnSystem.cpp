#include "RespawnSystem.h"

RespawnSystem::RespawnSystem()
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
			// respawn object
			ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(s->m_EntityID);

			TransformComponent* entityTransform = entity->GetComponent<TransformComponent>();
			entityTransform->SetPosition(s->m_RespawnPosition);
			entityTransform->SetRotation(s->m_RespawnOrientation);
			entity->SetActive(true);

			// remove from queue
			this->m_RespawnQueue.erase(s++);
		}
		else
		{
			++s;
		}
	}
}


void RespawnSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&RespawnSystem::OnGameObjectCreated);
	RegisterEventCallback(&RespawnSystem::OnGameObjectKilled);
}

void RespawnSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&RespawnSystem::OnGameObjectCreated);
	UnregisterEventCallback(&RespawnSystem::OnGameObjectKilled);
}

void RespawnSystem::OnGameObjectCreated(const GameObjectCreated * event)
{
	// register spawns ...
}

void RespawnSystem::OnGameObjectKilled(const GameObjectKilled * event)
{

	// check if entity has respawn ability
	RespawnComponent* entityRespawnComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<RespawnComponent>(event->m_EntityID);
	if (entityRespawnComponent != nullptr && entityRespawnComponent->IsActive())
	{
		// add to queue
		for (auto it = this->m_RespawnQueue.begin(); it != this->m_RespawnQueue.end(); ++it)
		{
			if (it->m_RemainingDeathTime > entityRespawnComponent->m_RespawnTime)
			{
				this->m_RespawnQueue.insert(it, PendingRespawn(event->m_EntityID, entityRespawnComponent->m_RespawnTime, entityRespawnComponent->m_RespawnPosition, entityRespawnComponent->m_RespawnOrientation));
			}
		}

		this->m_RespawnQueue.push_back(PendingRespawn(event->m_EntityID, entityRespawnComponent->m_RespawnTime, entityRespawnComponent->m_RespawnPosition, entityRespawnComponent->m_RespawnOrientation));
	}
}

