/*
	Author : Tobias Stein
	Date   : 11th July, 2016
	File   : IEventListener.h

	IEventListener interface allows a class to listen to events.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __I_EVENT_LISTENER_H__
#define __I_EVENT_LISTENER_H__

#include "EventDelegate.h"

#include "EventHandler.h"

namespace ECS
{
	namespace Event
	{
		class IEventListener
		{

		public:

			IEventListener()
			{}
			 
			~IEventListener()
			{}

			// Subscribe for an event 
			template<class E, class C>
			inline void RegisterEventCallback(void(C::*Callback)(const E* const))
			{
				Internal::IEventDelegate* eventDelegate = new Internal::EventDelegate<C, E>(static_cast<C*>(this), Callback);

				Log::Logger::GetInstance().LogTrace("\'%s\' subscribes for \'%s\' [%p]", typeid(C).name(), typeid(E).name(), eventDelegate);

				EventHandler::GetInstance().AddEventCallback<E>(eventDelegate);
			}

			// TODO!
			// Unsubscribe for event callbacks
			template<class E, class C>
			inline void UnregisterEventCallback(void(C::*Callback)(const E* const))
			{
				Internal::EventDelegateId eventDelegateId = (Internal::EventDelegateId)&(*static_cast<C*>(this));

				Log::Logger::GetInstance().LogTrace("\'%s\' unsubscribes from \'%s\'", typeid(C).name(), typeid(E).name());

				EventHandler::GetInstance().RemoveEventCallback<E>(eventDelegateId);
			}
		};

	} // namespace Event
} // namespace ECS

#endif // __I_EVENT_LISTENER_H__