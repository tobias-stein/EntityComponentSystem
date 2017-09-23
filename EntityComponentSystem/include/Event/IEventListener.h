/*
	Author : Tobias Stein
	Date   : 11th July, 2016
	File   : IEventListener.h

	IEventListener interface allows a class to listen to events.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_EVENT_LISTENER_H__
#define __I_EVENT_LISTENER_H__

#include "API.h"

#include "EventDelegate.h"

namespace ECS
{
	namespace Event
	{
		class ECS_API IEventListener
		{
		
		public:

			IEventListener();	 
			virtual ~IEventListener();

			// Subscribe for an event 
			template<class E, class C>
			inline void RegisterEventCallback(void(C::*Callback)(const E* const))
			{
				Internal::IEventDelegate* eventDelegate = new Internal::EventDelegate<C, E>(static_cast<C*>(this), Callback);
				ECS_Engine->SubscribeEvent<E>(eventDelegate);
			}

			// TODO!
			// Unsubscribe for event callbacks
			template<class E, class C>
			inline void UnregisterEventCallback(void(C::*Callback)(const E* const))
			{
				Internal::EventDelegateId eventDelegateId = (Internal::EventDelegateId)&(*static_cast<C*>(this));
				ECS_Engine->UnsubscribeEvent<E>(eventDelegateId);
			}
		};

	} // namespace Event
} // namespace ECS

#endif // __I_EVENT_LISTENER_H__