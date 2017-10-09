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

	public:
	
		// never use!
		EventDispatcher()
		{}
	
		~EventDispatcher()
		{}
	
		// send event to all listener
		inline void Dispatch(IEvent* event) override
		{
			LogTrace("Dispatch event %s", typeid(T).name());
	
			// if event is intend for only one listner
			for (EventDelegateList::iterator it = this->m_EventCallbacks.begin(); it != this->m_EventCallbacks.end(); ++it)
			{
				assert(it->second != nullptr && "Invalid event callback.");
	
				it->second->invoke(event);
			}
		}
	};

	DEFINE_STATIC_LOGGER_TEMPLATE(EventDispatcher, T, "EventDispatcher")

}}} // namespace ECS::Event::Internal

#endif // __EVENT_DISPATCHER_H__