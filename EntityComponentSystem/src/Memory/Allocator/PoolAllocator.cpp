/*
	Author : Tobias Stein
	Date   : 22nd October, 2016
	File   : PoolAllocator.cpp

	Pool allocator.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Memory/Allocator/PoolAllocator.h"

namespace ECS { namespace Memory { namespace Allocator {

	PoolAllocator::PoolAllocator(size_t memSize, const void* mem, size_t objectSize, u8 objectAlignment) :
		IAllocator(memSize, mem),
		OBJECT_SIZE(objectSize),
		OBJECT_ALIGNMENT(objectAlignment)
	{
		this->clear();
	}

	PoolAllocator::~PoolAllocator()
	{
		this->freeList = nullptr;
	}
	

	void* PoolAllocator::allocate(size_t memSize, u8 alignment)
	{
		assert(memSize > 0 && "allocate called with memSize = 0.");
		assert(memSize == this->OBJECT_SIZE && alignment == this->OBJECT_ALIGNMENT);

		if (this->freeList == nullptr)
			return nullptr;

		// get free slot
		void* p = this->freeList;

		// point to next free slot
		this->freeList = (void**)(*this->freeList);

		this->m_MemoryUsed += this->OBJECT_SIZE;
		this->m_MemoryAllocations++;

		return p;
	}


	void PoolAllocator::free(void* mem)
	{
		// put this slot back to free list
		*((void**)mem) = this->freeList;

		this->freeList = (void**)mem;

		this->m_MemoryUsed -= this->OBJECT_SIZE;
		this->m_MemoryAllocations--;
	}


	void PoolAllocator::clear()
	{
		u8 adjustment = GetAdjustment(this->m_MemoryFirstAddress, this->OBJECT_ALIGNMENT);
		
		size_t numObjects = (size_t)floor((this->m_MemorySize - adjustment) / this->OBJECT_SIZE);

		union
		{
			void* asVoidPtr;
			uptr asUptr;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;

		// align start address
		asUptr += adjustment;

		this->freeList = (void**)asVoidPtr;

		void** p = this->freeList;

		for (int i = 0; i < (numObjects - 1); ++i)
		{
			*p = (void*)((uptr)p + this->OBJECT_SIZE);

			 p = (void**)*p;
		}

		*p = nullptr;
	}

}}} // namespace ECS::Memory::Allocator