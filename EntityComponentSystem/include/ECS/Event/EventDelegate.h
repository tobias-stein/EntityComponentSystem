/*
	Author : Tobias Stein
	Date   : 26th July, 2016
	File   : EventDelegate.h
	
	A  delegate to forward events to specific handler methdos.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __EVENT_DELEGATE_H__
#define __EVENT_DELEGATE_H__

#include "Platform.h"

namespace ECS { namespace Event {

	class IEvent;
	
	namespace Internal
	{
		using EventDelegateId = size_t;
	
	
		class IEventDelegate
		{
		public:
	
			virtual inline void invoke(const IEvent* const e) = 0;
	
			virtual inline EventDelegateId GetDelegateId() const = 0;

			virtual inline u64 GetStaticEventTypeId() const = 0;

			virtual bool operator==(const IEventDelegate* other) const = 0;

			virtual IEventDelegate* clone() = 0;

		}; // class IEventDelegate
	
		template<class Class, class EventType>
		class EventDelegate : public IEventDelegate
		{
			typedef void(Class::*Callback)(const EventType* const);

			Class* m_Receiver;
			Callback m_Callback;
	
		public:
	
			EventDelegate(Class* receiver, Callback& callbackFunction) :
				m_Receiver(receiver),
				m_Callback(callbackFunction)
			{}

			virtual IEventDelegate* clone() override
			{
				return new EventDelegate(this->m_Receiver, this->m_Callback);
			}

			virtual inline void invoke(const IEvent* const e) override
			{
				(m_Receiver->*m_Callback)(reinterpret_cast<const EventType* const>(e));
			}
	
			virtual inline EventDelegateId GetDelegateId() const override
			{			
				static const EventDelegateId DELEGATE_ID { typeid(Class).hash_code() ^ typeid(Callback).hash_code() };
				return DELEGATE_ID;
			}


			virtual inline u64 GetStaticEventTypeId() const override
			{
				static const u64 SEID { EventType::STATIC_EVENT_TYPE_ID };
				return SEID;
			}			

			virtual bool operator==(const IEventDelegate* other) const override
			{
				if (this->GetDelegateId() != other->GetDelegateId())
					return false;

				EventDelegate* delegate = (EventDelegate*)other;
				if (other == nullptr)
					return false;

				return ((this->m_Callback == delegate->m_Callback) && (this->m_Receiver == delegate->m_Receiver));
			}

		}; // class EventDelegate
	
	}
}} // namespace ECS::Event::Internal

#endif // __EVENT_DELEGATE_H__