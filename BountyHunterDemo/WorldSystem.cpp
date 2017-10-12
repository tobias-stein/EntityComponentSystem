///-------------------------------------------------------------------------------------------------
/// File:	WorldSystem.cpp.
///
/// Summary:	Implements the world system class.
///-------------------------------------------------------------------------------------------------

#include "WorldSystem.h"

WorldSystem::WorldSystem(IWorld* world) :
	m_World(world),
	m_SpawnQueue(1024),
	m_KillQueue(1014),
	m_PendingSpawns(0),
	m_PendingKills(0)
{
	assert(world != nullptr && "WorldSystem can not be initialized with null-World!");
}

WorldSystem::~WorldSystem()
{
	// destroy the world.
	if (this->m_World != nullptr)
	{
		delete this->m_World;
		this->m_World = nullptr;
	}
}

void WorldSystem::PreUpdate(float dt)
{
	// process all pending spawns
	for (size_t i = 0; i < this->m_PendingSpawns; ++i)
	{
		if (this->m_SpawnQueue[i].m_EntityID != ECS::INVALID_ENTITY_ID)
		{
			ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(this->m_SpawnQueue[i].m_EntityID);

			// get entities transform
			TransformComponent* entityTransformComponent = entity->GetComponent<TransformComponent>();
			assert(entityTransformComponent != nullptr && "Failure! Spawned entity has no TransformComponent!");

			// set initial transform
			*entityTransformComponent = this->m_SpawnQueue[i].m_Transform;

			entity->SetActive(true);

			ECS::ECS_Engine->SendEvent<GameObjectSpawned>(this->m_SpawnQueue[i].m_EntityID, *entityTransformComponent);
		}
	}

	this->m_PendingSpawns = 0;
}

void WorldSystem::Update(float dt)
{}

void WorldSystem::PostUpdate(float dt)
{
	// process all pending kills
	for (size_t i = 0; i < this->m_PendingKills; ++i)
	{
		if (this->m_KillQueue[i] != ECS::INVALID_ENTITY_ID)
		{
			ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(this->m_KillQueue[i]);
			entity->SetActive(false);

			ECS::ECS_Engine->SendEvent<GameObjectKilled>(this->m_SpawnQueue[i].m_EntityID);
		}
	}

	this->m_PendingKills = 0;
}


void WorldSystem::SpawnGameObject(ECS::EntityId entityID, const Transform& transform)
{
	if (this->m_PendingSpawns < this->m_SpawnQueue.size())
	{
		this->m_SpawnQueue[this->m_PendingSpawns] = SpawnInfo(entityID, transform);
	}
	else
	{
		this->m_SpawnQueue.push_back(SpawnInfo(entityID, transform));
	}
	
	++this->m_PendingSpawns;
}

void WorldSystem::KillGameObject(ECS::EntityId entityID)
{
	if (this->m_PendingKills < this->m_KillQueue.size())
	{
		this->m_KillQueue[this->m_PendingKills] = entityID;
	}
	else
	{
		this->m_KillQueue.push_back(entityID);
	}

	++this->m_PendingKills;
}

void WorldSystem::RemoveGameObject(ECS::EntityId entityID)
{
	ECS::ECS_Engine->GetEntityManager()->DestroyEntity(entityID);

	// remove entity from spawn/kill
	for (size_t i = 0; i < this->m_PendingKills; ++i)
	{
		if (this->m_KillQueue[i] == entityID)
		{
			this->m_KillQueue[i] = ECS::INVALID_ENTITY_ID;
			return;
		}
	}

	for (size_t i = 0; i < this->m_PendingSpawns; ++i)
	{
		if (this->m_SpawnQueue[i].m_EntityID == entityID)
		{
			this->m_SpawnQueue[i].m_EntityID = ECS::INVALID_ENTITY_ID;
			return;
		}
	}
}
