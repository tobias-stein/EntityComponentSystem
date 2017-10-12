#include "RespawnSystem.h"

RespawnSystem::RespawnSystem()
{}

RespawnSystem::~RespawnSystem()
{}

void RespawnSystem::Update(float dt)
{
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
}

void RespawnSystem::OnGameObjectKilled(const GameObjectCreated * event)
{
}

