///-------------------------------------------------------------------------------------------------
/// File:	include\Platform.h.
///
/// Summary:	Declares the platform specifics.

#pragma once

#ifndef __PLATFORM_H__
#define __PLATFORM_H__


#ifdef ECS_EXPORT  
	#define ECS_API __declspec(dllexport)   
#else  
	#define ECS_API __declspec(dllimport)   
#endif  


// Check if using 64-Bit architecture
#ifdef _WIN64 || __x86_64__ || __ppc64__ || _M_AMD64 || _M_ARM64 || _M_X64
	#define ECS_64BIT 1

// Check if using 32-Bit architecture
#elif (_WIN32 && !_WIN64) || _M_IX86 
	#define ECS_32BIT 1
#endif



// Platform includes
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits>

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <functional>

#include <assert.h>
#include <memory>

#include <string>
#include <math.h>

#include <chrono>

namespace ECS
{

	// signed integer type
	using i8			= int8_t;
	using i16			= int16_t;
	using i32			= int32_t;

#ifdef ECS_64BIT
	using i64			= int64_t;
#else
	using i64			= int32_t;
#endif

	// unsigned integer type
	using u8			= uint8_t;
	using u16			= uint16_t;
	using u32			= uint32_t;
#ifdef ECS_64BIT
	using u64			= uint64_t;
#else
	using u64			= uint32_t;
#endif

	// floating point
	using f32			= float_t;
	using f64			= double_t;

	// pointer
	using iptr			= intptr_t;
	using uptr			= uintptr_t;

	using ObjectID		= u64;
	using TypeID		= u64;

	using TimeStamp		= u64;

	static const ObjectID	INVALID_OBJECT_ID	= std::numeric_limits<ObjectID>::max();
	static const TypeID		INVALID_TYPE_ID		= std::numeric_limits<TypeID>::max();

} // namespace ECS
	

#endif // __PLATFORM_H__