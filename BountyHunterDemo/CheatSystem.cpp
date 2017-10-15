///-------------------------------------------------------------------------------------------------
/// File:	CheatSystem.cpp.
///
/// Summary:	Implements the cheat system class.
///-------------------------------------------------------------------------------------------------

#include "CheatSystem.h"

#include <SDL.h>

#include "ControllerSystem.h"
#include "WorldSystem.h"

#include "Collector.h"
#include "Bounty.h"

#include "MaterialComponent.h"

CheatSystem::CheatSystem()
{
	SDL_Log("Cheats enabled!");

	RegisterEventCallbacks();

	this->m_ActivePlayerController = this->m_Controller.end();
}

CheatSystem::~CheatSystem()
{
	UnregisterEventCallbacks();
}

void CheatSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&CheatSystem::OnGameObjectCreated);
	RegisterEventCallback(&CheatSystem::OnGameObjectDestroyed);

	RegisterEventCallback(&CheatSystem::OnKeyDownEvent);
}

void CheatSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&CheatSystem::OnGameObjectCreated);
	UnregisterEventCallback(&CheatSystem::OnGameObjectDestroyed);
	
	UnregisterEventCallback(&CheatSystem::OnKeyDownEvent);
}

void CheatSystem::OnGameObjectCreated(const GameObjectCreated * event)
{
	// store controller
	ControllerComponent* entityControllerComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<ControllerComponent>(event->m_EntityID);
	if (entityControllerComponent != nullptr)
	{
		this->m_Controller.push_back(entityControllerComponent);
	}
}

void CheatSystem::OnGameObjectDestroyed(const GameObjectDestroyed * event)
{
	ControllerComponent* entityControllerComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<ControllerComponent>(event->m_EntityID);
	if (entityControllerComponent != nullptr)
	{
		this->m_Controller.remove(entityControllerComponent);
	}
}

void CheatSystem::OnKeyDownEvent(const KeyDownEvent * event)
{
	switch (event->keyCode)
	{

		// cheat: kill all player
		case SDLK_F5:	PossessCollector(); break;
		case SDLK_F6:	UnpossessCollector(); break;
		case SDLK_F7:	PossessNextCollector(); break;
		case SDLK_F8:	PossessPrevCollector(); break;

		case SDLK_F9:	KillAllCollectorGameObjects(); break;
		case SDLK_F10:	KillAllBountyGameObjects(); break;
	}
}


void CheatSystem::KillAllCollectorGameObjects()
{
	ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>()->KillAllGameObjects<Collector>();
}

void CheatSystem::KillAllBountyGameObjects()
{
	ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>()->KillAllGameObjects<Bounty>();
}

void CheatSystem::PossessCollector()
{
	// already possesses a collector?
	if (this->m_ActivePlayerController != this->m_Controller.end())
		return;

	this->m_ActivePlayerController = this->m_Controller.begin();

	DoPossessCollector();
}

void CheatSystem::UnpossessCollector()
{
	// no collector possessed?
	if (this->m_ActivePlayerController == this->m_Controller.end())
		return;

	DoUnpossessCollector();

	this->m_ActivePlayerController = this->m_Controller.end();
}

void CheatSystem::PossessNextCollector()
{
	// no collector possessed?
	if (this->m_ActivePlayerController == this->m_Controller.end())
		return;

	// unpossess current
	DoUnpossessCollector();

	// circle clock-wise
	this->m_ActivePlayerController++;
	if (this->m_ActivePlayerController == this->m_Controller.end())
		this->m_ActivePlayerController = this->m_Controller.begin();

	// possess next
	DoPossessCollector();
}

void CheatSystem::PossessPrevCollector()
{
	// no collector possessed?
	if (this->m_ActivePlayerController == this->m_Controller.end())
		return;

	// unpossess current
	DoUnpossessCollector();

	// circle counter-clock-wise
	if (this->m_ActivePlayerController == this->m_Controller.begin())
		this->m_ActivePlayerController = this->m_Controller.end();

	--this->m_ActivePlayerController;

	// possess next
	DoPossessCollector();
}

void CheatSystem::DoPossessCollector()
{
	// Indicate possessed Collector by changing its color
	MaterialComponent* collectorMaterialComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>((*this->m_ActivePlayerController)->GetOwner());
	assert(collectorMaterialComponent != nullptr && "Unable to retrieve collectors material component!");

	collectorMaterialComponent->SetColor(1.0f, 0.0f, 0.0f);
}

void CheatSystem::DoUnpossessCollector()
{
	// Reset color to default
	MaterialComponent* collectorMaterialComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>((*this->m_ActivePlayerController)->GetOwner());
	assert(collectorMaterialComponent != nullptr && "Unable to retrieve collectors material component!");

	collectorMaterialComponent->SetColor(MaterialComponent::DEFAULT_COLOR0);
}
