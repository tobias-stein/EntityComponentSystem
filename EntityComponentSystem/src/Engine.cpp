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

#include "util/Timer.h"

namespace ECS
{

	ECSEngine::ECSEngine()
	{
		ECS_EngineTime			= new util::Timer();
		ECS_EventHandler		= new Event::EventHandler();
		ECS_SystemManager		= new SystemManager();
		ECS_ComponentManager	= new ComponentManager();
		ECS_EntityManager		= new EntityManager(this->ECS_ComponentManager);
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

	void ECSEngine::Update(f32 tick_ms)
	{
		// Advance engine time
		ECS_EngineTime->Tick(tick_ms);

		// Update all running systems
		ECS_SystemManager->Update(tick_ms);
		ECS_EventHandler->DispatchEvents();

		// Finalize pending destroyed entities
		ECS_EntityManager->RemoveDestroyedEntities();
		ECS_EventHandler->DispatchEvents();
	}

	void ECSEngine::UnsubscribeEvent(Event::Internal::IEventDelegate* eventDelegate)
	{
		ECS_EventHandler->RemoveEventCallback(eventDelegate);
	}

} // namespace ECS