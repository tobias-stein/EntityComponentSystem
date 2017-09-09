/*
	Author : Tobias Stein
	Date   : 3rd September, 2017
	File   : CountByType.h

	A static counter that increments thee count for a specific type.

	All Rights Reserved. (c) Copyright 2016 - 2017.
*/

#include "util/StaticTypeCounter.h"

namespace ECS 
{ 
	class ISystem;
	class IComponent;

	namespace Event
	{
		class IEvent;
	}

	namespace util 
	{	

		u64 StaticTypeCounter<IComponent>::s_count = 0u;
		u64 StaticTypeCounter<ISystem>::s_count = 0u;
		u64 StaticTypeCounter<Event::IEvent> ::s_count = 0u;

		template class StaticTypeCounter<ISystem>;
		template class StaticTypeCounter<IComponent>;
		template class StaticTypeCounter<Event::IEvent>;
	}
} // namespace ECS::util