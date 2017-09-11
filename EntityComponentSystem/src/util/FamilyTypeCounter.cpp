/*
	Author : Tobias Stein
	Date   : 3rd September, 2017
	File   : CountByType.h

	A static counter that increments thee count for a specific type.

	All Rights Reserved. (c) Copyright 2016 - 2017.
*/

#include "util/FamilyTypeCounter.h"

namespace ECS
{
	class IEntity;
	class IComponent;
	class ISystem;
	

	namespace Event
	{
		class IEvent;
	}

	namespace util { namespace Internal {

		u64 FamilyTypeCounter<IEntity> ::s_count		= 0u;
		u64 FamilyTypeCounter<IComponent>::s_count		= 0u;
		u64 FamilyTypeCounter<ISystem>::s_count			= 0u;
		u64 FamilyTypeCounter<Event::IEvent> ::s_count	= 0u;
		
		template class FamilyTypeCounter<IEntity>;
		template class FamilyTypeCounter<IComponent>;
		template class FamilyTypeCounter<ISystem>;		
		template class FamilyTypeCounter<Event::IEvent>;
	}}

} // namespace ECS::util::Internal