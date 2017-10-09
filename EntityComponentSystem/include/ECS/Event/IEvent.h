/*
	Author : Tobias Stein
	Date   : 6th July, 2016
	File   : IEvent.h

	Base event class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_EVENT_H__
#define __I_EVENT_H__

#include "API.h"

namespace ECS { namespace Event {

		using EventTypeId		= TypeID;
		using EventTimestamp	= TimeStamp;

		static const EventTypeId INVALID_EVENTTYPE = INVALID_TYPE_ID;
		

		class ECS_API IEvent
		{
		private:

			EventTypeId		m_TypeId;
			EventTimestamp	m_TimeCreated;

		public:

			IEvent(EventTypeId typeId);
			 
			// ACCESSOR
			inline const EventTypeId	GetEventTypeID()	const { return this->m_TypeId; }
			inline const EventTimestamp GetTimeCreated()	const { return this->m_TimeCreated; }

		}; // class IEvent

}} // namespace ECS::Event

#endif // __I_EVENT_H__