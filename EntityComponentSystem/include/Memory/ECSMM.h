/*
	Author : Tobias Stein
	Date   : 6th September, 2017
	File   : ECSMM.h

	Internal used memory manager.

	All Rights Reserved. (c) Copyright 2016 - 2017.
*/

#ifndef __ECSSMM_H__
#define __ECSSMM_H__

#pragma once 

#define ECS_GLOBAL_MEMORY_CAPACITY 1073741824 // 1 GB

#include <memory>

#include "ECS.h"

#include "Log/ILogSubscriber.h"
#include "Memory/Allocator/StackAllocator.h"

namespace ECS { namespace Memory { 
	
	using StackAllocator = Allocator::StackAllocator;

	namespace Internal {


	class MemoryManager : protected Log::ILogSubscriber
	{
	public:

		friend class GlobalMemoryUser;

		static constexpr size_t MEMORY_CAPACITY = ECS_GLOBAL_MEMORY_CAPACITY;

	private:

		// Pointer to global allocated memory
		void*			m_GlobalMemory;

		// Allocator used to manager memory allocation from global memory
		StackAllocator*	m_MemoryAllocator;


		MemoryManager();
		MemoryManager(const MemoryManager&) = delete;
		MemoryManager& operator=(MemoryManager&) = delete;

		static inline std::shared_ptr<MemoryManager> GetInstance()
		{
			// Singleton
			static std::shared_ptr<MemoryManager> INSTANCE{ new MemoryManager };
			return INSTANCE;
		}

	public:

		

		~MemoryManager();


		inline const void* Allocate(size_t memSize, const char* user = nullptr)
		{
			LogDebug("%s allocated %d bytes of global memory.", user != nullptr ? user : "???", memSize);
			return m_MemoryAllocator->allocate(memSize, alignof(u8));
		}

		inline void Free(void* pMem)
		{
		}

	}; // class MemoryManager


	/**
	* Any class that wants to use global memory for allocations must derive from this class
	*/
	class GlobalMemoryUser
	{
	private:

		std::shared_ptr<MemoryManager> MEMORY_MANAGER;

	public:

		GlobalMemoryUser() : MEMORY_MANAGER(MemoryManager::GetInstance())
		{}

		virtual ~GlobalMemoryUser()
		{}

		inline const void* Allocate(size_t memSize, const char* user = nullptr)
		{
			return MEMORY_MANAGER->Allocate(memSize, user);
		}

		inline void Free(void* pMem)
		{
			MEMORY_MANAGER->Free(pMem);
		}
	};

}}} // namespace ECS::Memory::Internal

#endif // __ECSSMM_H__