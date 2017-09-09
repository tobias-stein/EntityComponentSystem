/*
	Author : Tobias Stein
	Date   : 22nd October, 2016
	File   : LinearAllocator.h

	Linear allocator.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __LINEAR_ALLOC_H__
#define __LINEAR_ALLOC_H__

#include "Memory/Allocator/IAllocator.h"

namespace ECS { namespace Memory { namespace Allocator {

	/*
		Allocates memory in a linear way. 

		      first          2   3   4
		    allocatation     alloaction
		        v            v   v   v
		|=================|=====|==|======| .... |
		^                                        ^
		Initialial                               Last possible
		memory                                   memory address
		address                                  (mem + memSize)
		(mem)


		memory only can be freed by clearing all allocations
	*/
	class ECS_API LinearAllocator : public IAllocator
	{
	public:

		LinearAllocator(size_t memSize, const void* mem);

		virtual ~LinearAllocator();

		virtual void* allocate(size_t size, u8 alignment) override;
		virtual void free(void* p) override;
		virtual void clear() override;

	}; // class LineaerAllocator

} } } // namespace ECS::Memory::Allocator

#endif // __LINEAR_ALLOC_H__