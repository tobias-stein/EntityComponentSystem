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

		static Log::Logger* s_Logger;

	public:
	
		// never use!
		EventDispatcher()
		{}
	
		~EventDispatcher()
		{}
	
		// send event to all listener
		inline void Dispatch(IEvent* event) override
		{
			s_Logger->LogTrace("Dispatch event %s", typeid(T).name());
	
			// if event is intend for only one listner
			for (EventDelegateList::iterator it = this->m_EventCallbacks.begin(); it != this->m_EventCallbacks.end(); ++it)
			{
				assert(it->second != nullptr && "Invalid event callback.");
	
				it->second->invoke(event);
			}
		}
	};

	template<class T>
	Log::Logger* EventDispatcher<T>::s_Logger = GetLogger("EventDispatcher");

}}} // namespace ECS::Event::Internal

#endif // __EVENT_DISPATCHER_H__