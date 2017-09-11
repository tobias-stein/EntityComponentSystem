///-------------------------------------------------------------------------------------------------
/// File:	src\API.cpp.
///
/// Summary:	Implements the API.


#include "API.h"

#include "Log/LoggerManager.h"
#include "Memory/ECSMM.h"

#include "Event/EventHandler.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace ECS
{

	// Create global manager objects.
	
	Log::Internal::LoggerManager* ECSLoggerManager		= new Log::Internal::LoggerManager();
	Memory::Internal::MemoryManager* ECSMemoryManager	= new Memory::Internal::MemoryManager();
	Event::EventHandler* ECSEventHandler				= new Event::EventHandler();
	SystemManager* ECSSystemManager						= new SystemManager();
	ComponentManager* ECSComponentManager				= new ComponentManager();	
	EntityManager* ECSEntityManager						= new EntityManager();
	
	

	

	void Terminate()
	{
		delete ECSEntityManager;
		ECSEntityManager = nullptr;

		delete ECSComponentManager;
		ECSComponentManager = nullptr;

		delete ECSSystemManager;
		ECSSystemManager = nullptr;

		delete ECSEventHandler;
		ECSEventHandler = nullptr;

		delete ECSMemoryManager;
		ECSMemoryManager = nullptr;

		delete ECSLoggerManager;
		ECSLoggerManager = nullptr;
	}

#if !ECS_DISABLE_LOGGING
	Log::Logger* GetLogger(const char* logger)
	{
		return ECSLoggerManager->GetLogger(logger);
	}
#endif

	namespace Memory
	{

		GlobalMemoryUser::GlobalMemoryUser() : ECS_MEMORY_MANAGER(ECSMemoryManager)
		{}

		GlobalMemoryUser::~GlobalMemoryUser()
		{}

		inline const void* GlobalMemoryUser::Allocate(size_t memSize, const char* user)
		{
			return ECS_MEMORY_MANAGER->Allocate(memSize, user);
		}

		inline void GlobalMemoryUser::Free(void* pMem)
		{
			ECS_MEMORY_MANAGER->Free(pMem);
		}
	} // namespace ECS::Memory

} // namespace ECS