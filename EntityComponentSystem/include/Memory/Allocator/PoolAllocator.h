/*
	Author : Tobias Stein
	Date   : 22nd October, 2016
	File   : PoolAllocator.h

	Pool allocator.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __POOL_ALLOC_H__
#define __POOL_ALLOC_H__


#include "Memory/Allocator/IAllocator.h"

namespace ECS { namespace Memory { namespace Allocator {

	class ECS_API PoolAllocator : public IAllocator
	{
	private:

		const size_t	OBJECT_SIZE;
		const u8		OBJECT_ALIGNMENT;

		void**			freeList;

	public:

		PoolAllocator::PoolAllocator(size_t memSize, const void* mem, size_t objectSize, u8 objectAlignment);

		virtual ~PoolAllocator();

		virtual void* allocate(size_t size, u8 alignment) override;
		virtual void free(void* p) override;
		virtual void clear() override;

	}; // class StackAllocator

}}} // namespace ECS::Memory::Allocator

#endif // __POOL_ALLOC_H__