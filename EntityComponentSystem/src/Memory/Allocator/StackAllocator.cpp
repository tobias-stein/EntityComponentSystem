/*
	Author : Tobias Stein
	Date   : 22nd October, 2016
	File   : StackAllocator.cpp

	Pool allocator.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Memory/Allocator/StackAllocator.h"

namespace ECS { namespace Memory { namespace Allocator {

	StackAllocator::StackAllocator(size_t memSize, const void* mem) :
		IAllocator(memSize, mem)
	{}

	StackAllocator::~StackAllocator()
	{
		this->clear();
	}

	void* StackAllocator::allocate(size_t memSize, u8 alignment)
	{
		assert(memSize > 0 && "allocate called with memSize = 0.");

		union
		{
			void* asVoidPtr;
			uptr asUptr;
			AllocMetaInfo* asMeta;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;

		// current address
		asUptr += this->m_MemoryUsed;

		u8 adjustment = GetAdjustment(asVoidPtr, alignment, sizeof(AllocMetaInfo));

		// check if there is enough memory available
		if (this->m_MemoryUsed + memSize + adjustment > this->m_MemorySize)
		{
			// not enough memory
			return nullptr;
		}

		// store alignment in allocation meta info
		asMeta->adjustment = adjustment;

		// determine aligned memory address
		asUptr += adjustment;

		// update book keeping
		this->m_MemoryUsed += memSize + adjustment;
		this->m_MemoryAllocations++;

		// return aligned memory address
		return asVoidPtr;
	}

	void StackAllocator::free(void* mem)
	{
		union
		{
			void* asVoidPtr;
			uptr asUptr;
			AllocMetaInfo* asMeta;
		};

		asVoidPtr = mem;
		
		// get meta info
		asUptr -= sizeof(AllocMetaInfo);

		// free used memory
		this->m_MemoryUsed -= ((uptr)this->m_MemoryFirstAddress + this->m_MemoryUsed) - ((uptr)mem + asMeta->adjustment);
			
		// decrement allocation count
		this->m_MemoryAllocations--;
	}

	void StackAllocator::clear()
	{
		// simply reset memory
		this->m_MemoryUsed = 0;
		this->m_MemoryAllocations = 0;
	}

} } } // namespace ECS::Memory::Allocator