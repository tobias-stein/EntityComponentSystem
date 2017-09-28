///-------------------------------------------------------------------------------------------------
/// File:	include\Platform.h.
///
/// Summary:	Declares the platform specifics.

#pragma once

#ifndef __PLATFORM_H__
#define __PLATFORM_H__


#ifdef ECS_EXPORTS  
	#define ECS_API __declspec(dllexport)   
#else  
	#define ECS_API __declspec(dllimport)   
#endif  

// Platform includes
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include <limits>

#include <math.h>

#include <assert.h>

#include <memory>

#include <string>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <functional>

namespace ECS
{

	// signed integer type
	using i8	= int8_t;
	using i16	= int16_t;
	using i32	= int32_t;
	using i64	= int64_t;

	// unsigned integer type
	using u8	= uint8_t;
	using u16	= uint16_t;
	using u32	= uint32_t;
	using u64	= uint64_t;

	// pointer
	using iptr  = intptr_t;
	using uptr	= uintptr_t;

} // namespace ECS


#endif // __PLATFORM_H__