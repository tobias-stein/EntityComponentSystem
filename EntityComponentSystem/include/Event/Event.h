/*
	Author : Tobias Stein
	Date   : 6th July, 2016
	File   : Event.h

	Event class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __EVENT_H__
#define __EVENT_H__

#include "Event/IEvent.h"

#include "util/FamilyTypeID.h"

namespace ECS { namespace Event {

	template<class T>
	class Event : public IEvent
	{

	public:
	
		// note: wont be part of stored event memory DATA
		static const EventTypeId STATIC_EVENT_TYPE_ID;
	
		Event(EntityId sender = ECS::INVALID_ENTITY_ID, EntityId receiver = ECS::INVALID_ENTITY_ID) :
			IEvent(STATIC_EVENT_TYPE_ID, 0u, sender, receiver) // todo: set timestamp
		{}

	}; // class Event<T>
	
	template<class T>
	const EventTypeId Event<T>::STATIC_EVENT_TYPE_ID = util::Internal::FamilyTypeID<IEvent>::Increment();

}} // namespace ECS::Event

#endif // __EVENT_H__