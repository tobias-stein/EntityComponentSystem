///-------------------------------------------------------------------------------------------------
/// File:	ControllerSystem.cpp.
///
/// Summary:	Implements the controller system class.
///-------------------------------------------------------------------------------------------------

#include "ControllerSystem.h"

ControllerSystem::ControllerSystem()
{
	RegisterEventCallbacks();
}

ControllerSystem::~ControllerSystem()
{
	UnregisterEventCallbacks();
}

void ControllerSystem::Update(float dt)
{
	for (auto C : this->m_Controller)
	{
		if (C->IsActive() == true)
		{
			C->Update(dt);
		}
	}
}

void ControllerSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&ControllerSystem::OnGameObjectCreated);
	RegisterEventCallback(&ControllerSystem::OnGameObjectDestroyed);
}

void ControllerSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&ControllerSystem::OnGameObjectCreated);
	UnregisterEventCallback(&ControllerSystem::OnGameObjectDestroyed);
}

void ControllerSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
	ControllerComponent* entityControllerComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<ControllerComponent>(event->m_EntityID);
	if (entityControllerComponent != nullptr)
	{
		this->m_Controller.push_back(entityControllerComponent);
	}
}

void ControllerSystem::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
	ControllerComponent* entityControllerComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<ControllerComponent>(event->m_EntityID);
	if (entityControllerComponent != nullptr)
	{
		this->m_Controller.remove(entityControllerComponent);
	}
}

