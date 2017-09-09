/*
	Author : Tobias Stein
	Date   : 22nd October, 2016
	File   : LinearAllocator.cpp

	Linear allocator.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Memory/Allocator/LinearAllocator.h"


namespace ECS { namespace Memory { namespace Allocator {

	LinearAllocator::LinearAllocator(size_t memSize, const void* mem) :
		IAllocator(memSize, mem)
	{}

	LinearAllocator::~LinearAllocator()
	{
		this->clear();
	}

	void* LinearAllocator::allocate(size_t memSize, u8 alignment)
	{
		assert(memSize > 0 && "allocate called with memSize = 0.");

		union
		{
			void* asVoidPtr;
			uptr asUptr;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;

		// current address
		asUptr += this->m_MemoryUsed;

		// get adjustment to align address
		u8 adjustment = GetAdjustment(asVoidPtr, alignment);

		// check if there is enough memory available
		if (this->m_MemoryUsed + memSize + adjustment > this->m_MemorySize)
		{
			// not enough memory
			return nullptr;
		}

		// determine aligned memory address
		asUptr += adjustment;

		// update book keeping
		this->m_MemoryUsed += memSize + adjustment;
		this->m_MemoryAllocations++;

		// return aligned memory address
		return asVoidPtr;
	}

	void LinearAllocator::free(void* mem)
	{
		assert(false && "Lineaer allocators do not support free operations. Use clear instead.");
	}

	void LinearAllocator::clear()
	{
		// simply reset memory
		this->m_MemoryUsed = 0;
		this->m_MemoryAllocations = 0;
	}

} } } // namespace ECS::Memory::Allocator