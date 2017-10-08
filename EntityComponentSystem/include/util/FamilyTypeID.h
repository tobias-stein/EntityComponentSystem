/*
	Author : Tobias Stein
	Date   : 8th October, 2016
	File   : CountByType.h
	
	A static counter that increments thee count for a specific type.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __FAMILY_TYPE_ID_H__
#define __FAMILY_TYPE_ID_H__


#include "API.h"

namespace ECS { namespace util { namespace Internal {

	template<class T>
	class ECS_API FamilyTypeID
	{
		static TypeID s_count;
	
	public:
	
		template<class U>
		static const TypeID Get()
		{
			static const TypeID STATIC_TYPE_ID { s_count++ };
			return STATIC_TYPE_ID;
		}

		static const TypeID Get()
		{
			return s_count;
		}
	};	

}}} // namespace ECS::util::Internal

#endif // __FAMILY_TYPE_ID_H__
