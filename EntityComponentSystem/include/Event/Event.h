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
	
		Event() : IEvent(STATIC_EVENT_TYPE_ID)
		{}

	}; // class Event<T>
	
	template<class T>
	const EventTypeId Event<T>::STATIC_EVENT_TYPE_ID { typeid(T).hash_code() };

}} // namespace ECS::Event

#endif // __EVENT_H__