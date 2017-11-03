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

namespace ECS { namespace Event {

	// forward declaration
	class IEvent;
	
	namespace Internal
	{
		class IEventDispatcher
		{
		public:
	
			virtual ~IEventDispatcher()
			{}
	
			virtual void Dispatch(IEvent* event) = 0;
	
			virtual void AddEventCallback(IEventDelegate* const eventDelegate) = 0;
	
			virtual void RemoveEventCallback(IEventDelegate* eventDelegate) = 0;
	
			virtual inline size_t GetEventCallbackCount() const = 0;
		};
	
	} // namespace Internal 

}} // namespace ECS::Event

#endif // __I_EVENT_DISPATCHER_H__