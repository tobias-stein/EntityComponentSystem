///-------------------------------------------------------------------------------------------------
/// File:	src\API.cpp.
///
/// Summary:	Implements the API.


#include "API.h"

#include "Log/LoggerManager.h"
#include "Memory/ECSMM.h"

namespace ECS
{
#if !ECS_DISABLE_LOGGING
	Log::Logger* GetLogger(const char* logger)
	{
		return Log::Internal::LoggerManager::GetInstance().GetLogger(logger);
	}
#endif

	namespace Memory
	{

		GlobalMemoryUser::GlobalMemoryUser() : ECS_MEMORY_MANAGER(Internal::MemoryManager::GetInstance())
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