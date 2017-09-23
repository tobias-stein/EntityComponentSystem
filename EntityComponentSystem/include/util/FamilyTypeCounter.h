/*
	Author : Tobias Stein
	Date   : 8th October, 2016
	File   : CountByType.h
	
	A static counter that increments thee count for a specific type.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __FAMILY_TYPE_COUNTER_H__
#define __FAMILY_TYPE_COUNTER_H__


#include "API.h"

namespace ECS { namespace util { namespace Internal {

	template<class T>
	class ECS_API FamilyTypeCounter
	{
		static u64 s_count;
	
	public:
	
		static inline u64 Increment()
		{
			return s_count++;
		}
	
		static inline const u64 Get()
		{
			return s_count;
		}
	};	

}}} // namespace ECS::util::Internal

#endif // __FAMILY_TYPE_COUNTER_H__
