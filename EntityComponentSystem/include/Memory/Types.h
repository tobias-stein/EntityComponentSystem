/*
	Author : Tobias Stein
	Date   : 10th July, 2016
	File   : Types.h

	Base memory types.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

namespace ECS
{
	using u8	= uint8_t;
	using u16	= uint16_t;
	using u32	= uint32_t;
	using u64	= uint64_t;

	using uptr = uintptr_t;

} // namespace ECS

#endif // __MEMORY_H__