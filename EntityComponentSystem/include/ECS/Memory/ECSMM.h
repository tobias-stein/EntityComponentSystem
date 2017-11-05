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

#define ECS_GLOBAL_MEMORY_CAPACITY 134217728 // 128 MB

#include "API.h"

#include "Memory/Allocator/StackAllocator.h"

namespace ECS { namespace Memory { namespace Internal {

	class Allocator::StackAllocator;

	class MemoryManager
	{
		friend class GlobalMemoryUser;

		using StackAllocator = Allocator::StackAllocator;
		
		DECLARE_LOGGER

	public:	

		static constexpr size_t MEMORY_CAPACITY = ECS_GLOBAL_MEMORY_CAPACITY;

	private:

		// Pointer to global allocated memory
		void*										m_GlobalMemory;

		// Allocator used to manager memory allocation from global memory
		StackAllocator*								m_MemoryAllocator;

		std::vector<std::pair<const char*, void*>>	m_PendingMemory;

		std::list<void*>							m_FreedMemory;

		MemoryManager(const MemoryManager&) = delete;
		MemoryManager& operator=(MemoryManager&) = delete;

	public:
		
		MemoryManager();
		~MemoryManager();


		inline void* Allocate(size_t memSize, const char* user = nullptr)
		{
			LogDebug("%s allocated %d bytes of global memory.", user != nullptr ? user : "Unknown", memSize);
			void* pMemory = m_MemoryAllocator->allocate(memSize, alignof(u8));

			this->m_PendingMemory.push_back(std::pair<const char*, void*>(user, pMemory));

			return pMemory;
		}

		inline void Free(void* pMem)
		{
			if (pMem == this->m_PendingMemory.back().second)
			{
				this->m_MemoryAllocator->free(pMem);
				this->m_PendingMemory.pop_back();

				bool bCheck = true;
				while(bCheck == true)
				{
					bCheck = false;

					// do not report already freed memory blocks.
					for (auto it : this->m_FreedMemory)
					{
						if (it == this->m_PendingMemory.back().second)
						{
							this->m_MemoryAllocator->free(pMem);
							this->m_PendingMemory.pop_back();
							this->m_FreedMemory.remove(it);

							bCheck = true;
							break;
						}
					}	
				};

			}
			else
			{
				this->m_FreedMemory.push_back(pMem);
			}
		}

		void CheckMemoryLeaks();

	}; // class MemoryManager

}}} // namespace ECS::Memory::Internal

#endif // __ECSSMM_H__