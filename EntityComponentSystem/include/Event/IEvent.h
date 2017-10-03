/*
	Author : Tobias Stein
	Date   : 6th July, 2016
	File   : IEvent.h

	Base event class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_EVENT_H__
#define __I_EVENT_H__


#include "IEntity.h"

namespace ECS { namespace Event {

		using EventTypeId		= TypeID;
		using EventTimestamp	= TimeStamp;

		static const EventTypeId INVALID_EVENTTYPE = INVALID_TYPE_ID;

		

		class ECS_API IEvent
		{
		private:

			EventTypeId		m_TypeId;
			EntityId		m_Sender;
			EntityId		m_Receiver;
			EventTimestamp	m_TimeCreated;

		public:

			IEvent(EventTypeId typeId, EntityId sender, EntityId receiver);
			 
			// ACCESSOR
			inline const EventTypeId	GetEventTypeID()	const { return this->m_TypeId; }
			inline const EntityId		GetSender()			const { return this->m_Sender; }
			inline const EntityId		GetReceiver()		const { return this->m_Receiver; }
			inline const EventTimestamp GetTimeCreated()	const { return this->m_TimeCreated; }

		}; // class IEvent

}} // namespace ECS::Event

#endif // __I_EVENT_H__