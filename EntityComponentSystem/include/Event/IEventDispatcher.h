/*
	Author : Tobias Stein
	Date   : 12th July, 2016
	File   : EventDispatcher.h

	Event dispatcher interface.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_EVENT_DISPATCHER_H__
#define __I_EVENT_DISPATCHER_H__

#include <unordered_map>

#include "EventDelegate.h"

namespace ECS
{
	namespace Event
	{
		// forward declaration
		class IEvent;

		namespace Internal
		{
			class IEventDispatcher
			{
			protected:

				using EventDelegateList = std::unordered_map<EventDelegateId,IEventDelegate*>;

				EventDelegateList	m_EventCallbacks;

			public:


				IEventDispatcher() :
					m_EventCallbacks(EventDelegateList())
				{}

				~IEventDispatcher()
				{
					this->m_EventCallbacks.clear();
				}

				// send event to all listener
				virtual inline void Dispatch(IEvent* event)
				{}

				inline void AddEventCallback(IEventDelegate* const eventDelegate)
				{
					EventDelegateId id = (EventDelegateId)eventDelegate->GetId();

					EventDelegateList::const_iterator it = this->m_EventCallbacks.find(id);

					assert(it == this->m_EventCallbacks.end() && "Event callback already registered.");
					if (it != this->m_EventCallbacks.end())
						return;

					this->m_EventCallbacks[id] = eventDelegate;
				}

				inline void RemoveEventCallback(size_t eventDelegateId)
				{
					this->m_EventCallbacks.erase(eventDelegateId);
				}

				inline int GetEventCallbackCount() const
				{
					return this->m_EventCallbacks.size();
				}
			};

		} // namespace Internal
	} // namespace Event
} // namespace ECS

#endif // __I_EVENT_DISPATCHER_H__