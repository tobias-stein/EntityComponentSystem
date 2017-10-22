///-------------------------------------------------------------------------------------------------
/// File:	WorldSystem.cpp.
///
/// Summary:	Implements the world system class.
///-------------------------------------------------------------------------------------------------

#include "WorldSystem.h"

WorldSystem::WorldSystem(IWorld* world) :
	m_World(world),
	m_WorldObjects(1024),
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
		if (this->m_SpawnQueue[i].m_GameObjectID != INVALID_GAMEOBJECT_ID)
		{
			ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(this->m_SpawnQueue[i].m_GameObjectID);

			// get entities transform
			TransformComponent* entityTransformComponent = entity->GetComponent<TransformComponent>();
			assert(entityTransformComponent != nullptr && "Failure! Spawned entity has no TransformComponent!");

			// set initial transform
			*entityTransformComponent = this->m_SpawnQueue[i].m_Transform;

			entity->SetActive(true);

			ECS::ECS_Engine->SendEvent<GameObjectSpawned>(this->m_SpawnQueue[i].m_GameObjectID, *entityTransformComponent);
		}
	}

	this->m_PendingSpawns = 0;
}

void WorldSystem::Update(float dt)
{
	this->m_World->Update(dt);
}

void WorldSystem::PostUpdate(float dt)
{
	// process all pending kills
	for (size_t i = 0; i < this->m_PendingKills; ++i)
	{
		if (this->m_KillQueue[i] != INVALID_GAMEOBJECT_ID)
		{
			ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(this->m_KillQueue[i]);
			entity->SetActive(false);

			ECS::ECS_Engine->SendEvent<GameObjectKilled>(this->m_KillQueue[i]);
		}
	}

	this->m_PendingKills = 0;
}


void WorldSystem::SpawnGameObject(GameObjectId gameObjectId, const Transform& transform)
{
	if (this->m_PendingSpawns < this->m_SpawnQueue.size())
	{
		this->m_SpawnQueue[this->m_PendingSpawns] = SpawnInfo(gameObjectId, transform);
	}
	else
	{
		this->m_SpawnQueue.push_back(SpawnInfo(gameObjectId, transform));
	}
	
	++this->m_PendingSpawns;
}

void WorldSystem::KillGameObject(GameObjectId gameObjectId)
{
	if (this->m_PendingKills < this->m_KillQueue.size())
	{
		this->m_KillQueue[this->m_PendingKills] = gameObjectId;
	}
	else
	{
		this->m_KillQueue.push_back(gameObjectId);
	}

	++this->m_PendingKills;
}

void WorldSystem::RemoveGameObject(GameObjectId gameObjectId)
{
	this->m_World->RemoveGameObject(gameObjectId);

	ECS::ECS_Engine->GetEntityManager()->DestroyEntity(gameObjectId);

	for (size_t i = 0; i < this->m_WorldObjects.size(); ++i)
	{
		if (this->m_WorldObjects[i].m_GameObjectID == gameObjectId)
		{
			this->m_WorldObjects[i].m_GameObjectID = INVALID_GAMEOBJECT_ID;
			this->m_WorldObjects[i].m_GameObjectType = ECS::INVALID_TYPE_ID;

			ECS::ECS_Engine->SendEvent<GameObjectDestroyed>(gameObjectId, this->m_WorldObjects[i].m_GameObjectType);
			break;
		}
	}

	// remove entity from spawn/kill
	for (size_t i = 0; i < this->m_PendingKills; ++i)
	{
		if (this->m_KillQueue[i] == gameObjectId)
		{
			this->m_KillQueue[i] = ECS::INVALID_ENTITY_ID;
			return;
		}
	}

	for (size_t i = 0; i < this->m_PendingSpawns; ++i)
	{
		if (this->m_SpawnQueue[i].m_GameObjectID == gameObjectId)
		{
			this->m_SpawnQueue[i].m_GameObjectID = INVALID_GAMEOBJECT_ID;
			return;
		}
	}
}

void WorldSystem::Clear()
{
	for (size_t i = 0; i < this->m_WorldObjects.size(); ++i)
	{
		if (this->m_WorldObjects[i].m_GameObjectID != INVALID_GAMEOBJECT_ID)
		{
			ECS::ECS_Engine->GetEntityManager()->DestroyEntity(this->m_WorldObjects[i].m_GameObjectID);
			ECS::ECS_Engine->SendEvent<GameObjectDestroyed>(this->m_WorldObjects[i].m_GameObjectID, this->m_WorldObjects[i].m_GameObjectType);

			this->m_WorldObjects[i].m_GameObjectID = INVALID_GAMEOBJECT_ID;
			this->m_WorldObjects[i].m_GameObjectType = ECS::INVALID_TYPE_ID;
		}
	}

	this->m_PendingKills = 0;
	this->m_PendingSpawns = 0;

	this->m_World->Clear();
}
