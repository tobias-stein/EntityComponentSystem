///-------------------------------------------------------------------------------------------------
/// File:	LifetimeSystem.cpp.
///
/// Summary:	Implements the lifetime system class.
///-------------------------------------------------------------------------------------------------

#include "LifetimeSystem.h"

#include "MaterialComponent.h"

LifetimeSystem::LifetimeSystem()
{
	this->m_WorldSystem = ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>();
	RegisterEventCallbacks();
}

LifetimeSystem::~LifetimeSystem()
{
	UnregisterEventCallbacks();
}


void LifetimeSystem::Update(float dt)
{
	return;

	auto ltc = this->m_ActiveLifetimeComponents.begin();
	while (ltc != this->m_ActiveLifetimeComponents.end())
	{
		(*ltc)->currentLifetime -= dt;
		if ((*ltc)->currentLifetime <= 0.0f)
		{
			// kill game object, life time is up.
			this->m_WorldSystem->KillGameObject((*ltc)->GetOwner());

			// remove from active lifetime component list
			this->m_ActiveLifetimeComponents.erase(ltc++);
		}
		else
		{
			MaterialComponent* mc = ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>((*ltc)->GetOwner());
			if (mc != nullptr)
			{
				Color4f color = mc->GetColor();
				color.a = glm::min<float>((*ltc)->currentLifetime / (*ltc)->minLifetime, 1.0f);
				mc->SetColor(color);
			}

			++ltc;
		}
	}
}

void LifetimeSystem::Reset()
{
	this->m_ActiveLifetimeComponents.clear();
}


void LifetimeSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&LifetimeSystem::OnGameObjectCreated);
	RegisterEventCallback(&LifetimeSystem::OnGameObjectDestroyed);
	RegisterEventCallback(&LifetimeSystem::OnGameObjectSpawned);
	RegisterEventCallback(&LifetimeSystem::OnGameObjectKilled);
}

void LifetimeSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&LifetimeSystem::OnGameObjectCreated);
	UnregisterEventCallback(&LifetimeSystem::OnGameObjectDestroyed);
	UnregisterEventCallback(&LifetimeSystem::OnGameObjectSpawned);
	UnregisterEventCallback(&LifetimeSystem::OnGameObjectKilled);
}

void LifetimeSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
	LifetimeComponent* ltc = ECS::ECS_Engine->GetComponentManager()->GetComponent<LifetimeComponent>(event->m_EntityID);
	if (ltc != nullptr)
	{
		this->m_ActiveLifetimeComponents.push_back(ltc);
	}
}

void LifetimeSystem::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
	LifetimeComponent* ltc = ECS::ECS_Engine->GetComponentManager()->GetComponent<LifetimeComponent>(event->m_EntityID);
	if (ltc != nullptr)
	{
		this->m_ActiveLifetimeComponents.remove(ltc);
	}
}

void LifetimeSystem::OnGameObjectSpawned(const GameObjectSpawned* event)
{
	LifetimeComponent* ltc = ECS::ECS_Engine->GetComponentManager()->GetComponent<LifetimeComponent>(event->m_EntityID);
	if (ltc != nullptr)
	{
		this->m_ActiveLifetimeComponents.remove(ltc);
		this->m_ActiveLifetimeComponents.push_back(ltc);
	}
}

void LifetimeSystem::OnGameObjectKilled(const GameObjectKilled* event)
{
	LifetimeComponent* ltc = ECS::ECS_Engine->GetComponentManager()->GetComponent<LifetimeComponent>(event->m_EntityID);
	if (ltc != nullptr)
	{
		this->m_ActiveLifetimeComponents.remove(ltc);
	}
}
