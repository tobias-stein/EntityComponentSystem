/*
	Author : Tobias Stein
	Date   : 9th July, 2016
	File   : IAllocator.h

	Base allocator class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_ALLOC_H__
#define __I_ALLOC_H__

#include "API.h"

namespace ECS { namespace Memory { namespace Allocator {


	// returns address aligned
	static inline void* AlignForward(void* address, u8 alignment)
	{
		return (void*)((reinterpret_cast<uptr>(address)+static_cast<uptr>(alignment - 1)) & static_cast<uptr>(~(alignment - 1)));
	}
	
	// returns the number of bytes needed to align the address
	static inline u8 GetAdjustment(const void* address, u8 alignment)
	{
		u8 adjustment = alignment - (reinterpret_cast<uptr>(address)& static_cast<uptr>(alignment - 1));
	
		return adjustment == alignment ? 0 : adjustment;
	}
	
	static inline u8 GetAdjustment(const void* address, u8 alignment, u8 extra)
	{
		u8 adjustment = GetAdjustment(address, alignment);
	
		u8 neededSpace = extra;
	
		if (adjustment < neededSpace)
		{
			neededSpace -= adjustment;
	
			//Increase adjustment to fit header
			adjustment += alignment * (neededSpace / alignment);
	
			if (neededSpace % alignment > 0)
				adjustment += alignment;
		}
	
		return adjustment;
	}
	
	
	class ECS_API IAllocator
	{
	protected:
	
		const size_t		m_MemorySize;
		const void*			m_MemoryFirstAddress;
	
		size_t				m_MemoryUsed;
		u64					m_MemoryAllocations;
	
	public:
	
		IAllocator(const size_t memSize, const void* mem);
		virtual ~IAllocator();
	
		virtual void* allocate(size_t size, u8 alignment) = 0;
		virtual void free(void* p) = 0;
		virtual void clear() = 0;
	
		// ACCESSOR
		inline size_t GetMemorySize() const
		{
			return this->m_MemorySize;
		}
	
		inline const void* GetMemoryAddress0() const
		{
			return this->m_MemoryFirstAddress;
		}
	
		inline size_t GetUsedMemory() const
		{
			return this->m_MemoryUsed;
		}
	
		inline u64 GetAllocationCount() const
		{
			return this->m_MemoryAllocations;
		}
	
	};

}}} // ECS::Memory::Allocator

#endif // __I_ALLOC_H__ 