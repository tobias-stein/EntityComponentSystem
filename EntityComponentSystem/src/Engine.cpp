///-------------------------------------------------------------------------------------------------
/// File:	src\Engine.cpp.
///
/// Summary:	Implements the engine class.
///-------------------------------------------------------------------------------------------------


#include "Engine.h"

#include "Event/EventHandler.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace ECS
{

	ECSEngine::ECSEngine()
	{
		ECS_EventHandler		= new Event::EventHandler();
		ECS_SystemManager		= new SystemManager();
		ECS_ComponentManager	= new ComponentManager();
		ECS_EntityManager		= new EntityManager();
	}

	ECSEngine::~ECSEngine()
	{
		delete ECS_EntityManager;
		ECS_EntityManager = nullptr;

		delete ECS_ComponentManager;
		ECS_ComponentManager = nullptr;

		delete ECS_SystemManager;
		ECS_SystemManager = nullptr;

		delete ECS_EventHandler;
		ECS_EventHandler = nullptr;
	}

	void ECSEngine::Update()
	{
		// Dispatch all events accumulated last frame
		ECS_EventHandler->DispatchEvents();

		// Update all running systems
		ECS_SystemManager->Update();
	}

	void ECSEngine::UnsubscribeEvent(u64 typeId, Event::Internal::EventDelegateId eventDelegateId)
	{
		ECS_EventHandler->RemoveEventCallback(typeId, eventDelegateId);
	}

} // namespace ECS