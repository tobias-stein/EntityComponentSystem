/*
	Author : Tobias Stein
	Date   : 6th July, 2016
	File   : Event.h

	Event class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __EVENT_H__
#define __EVENT_H__

#include "IEvent.h"
#include "EventHandler.h"

#include "../util/StaticTypeCounter.h"

#include "../Log/Logger.h"

namespace ECS { namespace Event {

	template<class T>
	class Event : public IEvent
	{
	public:
	
		// note: wont be part of stored event memory DATA
		static const EventTypeId STATIC_EVENT_TYPE_ID;
	
	public:
	
		Event(EntityId sender = INVALID_ENITYID, EntityId receiver = INVALID_ENITYID) :
			IEvent(STATIC_EVENT_TYPE_ID, 0u, sender, receiver) // todo: set timestamp
		{}
	
	private:
	
		static inline const u64 SetEventTypeId()
		{
			u64 EID = util::StaticTypeCounter<IEvent>::Increment();
			Log::Logger::GetInstance().LogDebug("Register event \'%s\' [EVENT-ID: %d]", typeid(T).name(), EID);
			return EID;
		}
	};
	
	template<class T>
	const EventTypeId Event<T>::STATIC_EVENT_TYPE_ID = Event<T>::SetEventTypeId();

}} // namespace ECS::Event

#endif // __EVENT_H__