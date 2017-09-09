/*
	Author : Tobias Stein
	Date   : 6th September, 2017
	File   : ECSMM.cpp

	Internal used memory manager.

	All Rights Reserved. (c) Copyright 2016 - 2017.
*/

#include "Memory/ECSMM.h"

#include <stdlib.h>
#include <assert.h>

namespace ECS { namespace Memory { namespace Internal {

	MemoryManager::MemoryManager() : ILogSubscriber("MemoryManager")
	{		
		LogInfo("Initialize MemoryManager!");

		// allocate global memory
		this->m_GlobalMemory = malloc(MemoryManager::MEMORY_CAPACITY);
		if (this->m_GlobalMemory != nullptr)
		{
			LogInfo("%d bytes of memory allocated.", MemoryManager::MEMORY_CAPACITY);
		}
		else
		{
			LogFatal("Failed to allocate %d bytes of memory!", MemoryManager::MEMORY_CAPACITY);
			assert(this->m_GlobalMemory != nullptr && "Failed to allocate global memory.");
		}

		// create allocator
		this->m_MemoryAllocator = new StackAllocator(MemoryManager::MEMORY_CAPACITY, this->m_GlobalMemory);
		assert(this->m_MemoryAllocator != nullptr && "Failed to create memory allocator!");
	}

	MemoryManager::~MemoryManager()
	{
		LogInfo("Releasing MemoryManager!");

		this->m_MemoryAllocator->clear();

		delete this->m_MemoryAllocator;
		this->m_MemoryAllocator = nullptr;

		free(this->m_GlobalMemory);
		this->m_GlobalMemory = nullptr;
	}

}}} // namespace ECS::Memory::Internal
