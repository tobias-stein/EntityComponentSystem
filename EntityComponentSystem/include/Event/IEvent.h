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

		using EventTypeId = util::TypeId;

		static const EventTypeId INVALID_EVENTTYPE = util::INVALID_TYPE_ID;

		using EventTimestamp = u64;

		class IEvent
		{

		public:

			EventTypeId		m_TypeId;
			EntityId		m_Sender;
			EntityId		m_Receiver;
			EventTimestamp	m_TimeCreated;

		public:

			IEvent(EventTypeId typeId, EventTimestamp created, EntityId sender, EntityId receiver) :
				m_TypeId(typeId),
				m_Sender(sender),
				m_Receiver(receiver),
				m_TimeCreated(created)
			{}

			// ACCESSOR
			inline const EventTypeId	GetEventTypeID() const { return this->m_TypeId; }

			inline const EntityId		GetSender() const { return this->m_Sender; }
			inline const EntityId		GetReceiver() const { return this->m_Receiver; }

			inline const EventTimestamp GetTimeCreated() const { return this->m_TimeCreated; }

		}; // class IEvent

}} // namespace ECS::Event

#endif // __I_EVENT_H__