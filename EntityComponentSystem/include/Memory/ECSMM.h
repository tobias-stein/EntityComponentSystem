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

#include "API.h"

#include "Memory/Allocator/StackAllocator.h"

namespace ECS { namespace Memory { namespace Internal {

	class Allocator::StackAllocator;

	class MemoryManager
	{
		friend class GlobalMemoryUser;

		using StackAllocator = Allocator::StackAllocator;

		static Log::Logger* s_Logger;


	public:	

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
			s_Logger->LogDebug("%s allocated %d bytes of global memory.", user != nullptr ? user : "???", memSize);
			return m_MemoryAllocator->allocate(memSize, alignof(u8));
		}

		inline void Free(void* pMem)
		{
		}

	}; // class MemoryManager

}}} // namespace ECS::Memory::Internal

#endif // __ECSSMM_H__