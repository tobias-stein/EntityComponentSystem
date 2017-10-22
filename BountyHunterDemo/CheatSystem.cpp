///-------------------------------------------------------------------------------------------------
/// File:	CheatSystem.cpp.
///
/// Summary:	Implements the cheat system class.
///-------------------------------------------------------------------------------------------------

#include "CheatSystem.h"

#include <SDL.h>

#include "ControllerSystem.h"
#include "WorldSystem.h"
#include "PlayerSystem.h"

#include "Collector.h"
#include "Bounty.h"

#include "AICollectorController.h"
#include "PlayerCollectorController.h"

#include "MaterialComponent.h"

CheatSystem::CheatSystem()
{
	SDL_Log("Cheats enabled!");

	RegisterEventCallbacks();

	this->m_SelectedPlayer = this->m_Players.end();
}

CheatSystem::~CheatSystem()
{
	UnregisterEventCallbacks();
}

void CheatSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&CheatSystem::OnGameObjectCreated);
	RegisterEventCallback(&CheatSystem::OnGameObjectDestroyed);

	RegisterEventCallback(&CheatSystem::OnPlayerJoined);
	RegisterEventCallback(&CheatSystem::OnPlayerLeft);

	RegisterEventCallback(&CheatSystem::OnKeyDownEvent);
}

void CheatSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&CheatSystem::OnGameObjectCreated);
	UnregisterEventCallback(&CheatSystem::OnGameObjectDestroyed);
	
	UnregisterEventCallback(&CheatSystem::OnPlayerJoined);
	UnregisterEventCallback(&CheatSystem::OnPlayerLeft);

	UnregisterEventCallback(&CheatSystem::OnKeyDownEvent);
}

void CheatSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
}

void CheatSystem::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
}

void CheatSystem::OnPlayerJoined(const PlayerJoined* event)
{
	this->m_Players.push_back(event->playerID);
}

void CheatSystem::OnPlayerLeft(const PlayerLeft* event)
{
	this->m_Players.remove(event->playerID);
}

void CheatSystem::OnKeyDownEvent(const KeyDownEvent* event)
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

		case SDLK_F11:	DumpPhysics(); break;
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
	if (this->m_SelectedPlayer != this->m_Players.end())
		return;

	this->m_SelectedPlayer = this->m_Players.begin();

	DoPossessCollector();
}

void CheatSystem::UnpossessCollector()
{
	// no collector possessed?
	if (this->m_SelectedPlayer == this->m_Players.end())
		return;

	DoUnpossessCollector();

	this->m_SelectedPlayer = this->m_Players.end();
}

void CheatSystem::PossessNextCollector()
{
	// no collector possessed?
	if (this->m_SelectedPlayer == this->m_Players.end())
		return;

	// unpossess current
	DoUnpossessCollector();

	// circle clock-wise
	this->m_SelectedPlayer++;
	if (this->m_SelectedPlayer == this->m_Players.end())
		this->m_SelectedPlayer = this->m_Players.begin();

	// possess next
	DoPossessCollector();
}

void CheatSystem::PossessPrevCollector()
{
	// no collector possessed?
	if (this->m_SelectedPlayer == this->m_Players.end())
		return;

	// unpossess current
	DoUnpossessCollector();

	// circle counter-clock-wise
	if (this->m_SelectedPlayer == this->m_Players.begin())
		this->m_SelectedPlayer = this->m_Players.end();

	--this->m_SelectedPlayer;

	// possess next
	DoPossessCollector();
}

void CheatSystem::DoPossessCollector()
{
	Player* player = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>()->GetPlayer(*this->m_SelectedPlayer);

	GameObjectId pawn = player->GetController().GetPossessed();

	// Indicate possessed Collector by changing its color
	MaterialComponent* collectorMaterialComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>(pawn);
	assert(collectorMaterialComponent != nullptr && "Unable to retrieve collectors material component!");

	collectorMaterialComponent->SetColor(1.0f, 0.0f, 0.0f);

	// Release old controller
	player->GetController().Release();

	// give player controll
	player->GetController().SetController(new PlayerCollectorController(pawn, *this->m_SelectedPlayer));
}

void CheatSystem::DoUnpossessCollector()
{
	Player* player = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>()->GetPlayer(*this->m_SelectedPlayer);

	GameObjectId pawn = player->GetController().GetPossessed();

	// Reset color to default
	MaterialComponent* collectorMaterialComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>(pawn);
	assert(collectorMaterialComponent != nullptr && "Unable to retrieve collectors material component!");

	collectorMaterialComponent->SetColor(MaterialComponent::DEFAULT_COLOR0);

	// Release old controller
	player->GetController().Release();

	// let AI take controll
	player->GetController().SetController(new AICollectorController(pawn, *this->m_SelectedPlayer));
}

void CheatSystem::DumpPhysics()
{
	ECS::ECS_Engine->GetSystemManager()->GetSystem<WorldSystem>()->DumpPhysics();
}
