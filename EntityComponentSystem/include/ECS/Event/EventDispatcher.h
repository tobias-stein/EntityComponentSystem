/*
	Author : Tobias Stein
	Date   : 10th July, 2016
	File   : EventDispatcher.h

	Un/Registers subscribers for events and dispatches forwards incoming events.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include "API.h"
#include "IEventDispatcher.h"

namespace ECS { namespace Event { namespace Internal {

	template<class T>
	class EventDispatcher : public IEventDispatcher
	{
		DECLARE_STATIC_LOGGER

		using EventDelegateList			= std::unordered_map<EventDelegateId, IEventDelegate*>;
		//using PendingAddDelegates		= std::list<IEventDelegate*>;
		using PendingRemoveDelegates	= std::list<EventDelegateId>;	

		//PendingAddDelegates		m_PendingAddDelegates;
		PendingRemoveDelegates	m_PendingRemoveDelegates;

		EventDelegateList		m_EventCallbacks;

		bool					m_Locked;

	public:
	
		// never use!
		EventDispatcher() :
			m_EventCallbacks(EventDelegateList()),
			m_Locked(false)
		{}
	
		virtual ~EventDispatcher()
		{
			//this->m_PendingAddDelegates.clear();
			this->m_PendingRemoveDelegates.clear();
			this->m_EventCallbacks.clear();
		}
	
		// send event to all listener
		inline void Dispatch(IEvent* event) override
		{
			this->m_Locked = true;
			{
				LogTrace("Dispatch event %s", typeid(T).name());

				// remove pending delegates
				if (this->m_PendingRemoveDelegates.empty() == false)
				{
					for (auto EC : this->m_PendingRemoveDelegates)
						this->m_EventCallbacks.erase(EC);

					this->m_PendingRemoveDelegates.clear();
				}

				auto EC = this->m_EventCallbacks.begin();
				while (EC != this->m_EventCallbacks.end())
				{
					assert(EC->second != nullptr && "Invalid event callback.");
					EC->second->invoke(event);
					++EC;
				}
			}
			this->m_Locked = false;
		}

		virtual void AddEventCallback(IEventDelegate* const eventDelegate) override
		{
			EventDelegateId id = (EventDelegateId)eventDelegate->GetDelegateId();

			EventDelegateList::const_iterator it = this->m_EventCallbacks.find(id);

			// no duplicate
			if (it != this->m_EventCallbacks.end())
				return;

			this->m_EventCallbacks[id] = eventDelegate;
		}

		virtual void RemoveEventCallback(size_t eventDelegateId) override
		{ 
			if (this->m_Locked == false)
			{
				this->m_EventCallbacks.erase(eventDelegateId);
			}
			else
			{
				this->m_PendingRemoveDelegates.push_back(eventDelegateId);
			}
		}

		virtual inline size_t GetEventCallbackCount() const override { return this->m_EventCallbacks.size(); }
	};

	DEFINE_STATIC_LOGGER_TEMPLATE(EventDispatcher, T, "EventDispatcher")

}}} // namespace ECS::Event::Internal

#endif // __EVENT_DISPATCHER_H__