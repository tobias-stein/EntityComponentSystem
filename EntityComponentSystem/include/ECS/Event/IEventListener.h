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
		///-------------------------------------------------------------------------------------------------
		/// Class:	ECS_API
		///
		/// Summary:	Allows a deriving class to participate in eventing.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///-------------------------------------------------------------------------------------------------

		class ECS_API IEventListener
		{	
			using RegisteredCallbacks = std::list<Internal::IEventDelegate*>;
			RegisteredCallbacks m_RegisteredCallbacks;

		public:

			IEventListener();	 
			virtual ~IEventListener();

			///-------------------------------------------------------------------------------------------------
			/// Fn:	template<class E, class C> inline void IEventListener::RegisterEventCallback(void(C::*Callback)(const E* const))
			///
			/// Summary:	Registers the event callback described by Callback.
			///
			/// Author:	Tobias Stein
			///
			/// Date:	24/09/2017
			///
			/// Typeparams:
			/// E - 	   	Type of the e.
			/// C - 	   	Type of the c.
			/// Parameters:
			/// Callback - 	[in,out] If non-null, the callback.
			///-------------------------------------------------------------------------------------------------

			template<class E, class C>
			inline void RegisterEventCallback(void(C::*Callback)(const E* const))
			{

				Internal::IEventDelegate* eventDelegate = new Internal::EventDelegate<C, E>(static_cast<C*>(this), Callback);

				m_RegisteredCallbacks.push_back(eventDelegate);
				ECS_Engine->SubscribeEvent<E>(eventDelegate);
			}

			///-------------------------------------------------------------------------------------------------
			/// Fn:	template<class E, class C> inline void IEventListener::UnregisterEventCallback(void(C::*Callback)(const E* const))
			///
			/// Summary:	Unregisters the event callback described by Callback.
			///
			/// Author:	Tobias Stein
			///
			/// Date:	24/09/2017
			///
			/// Typeparams:
			/// E - 	   	Type of the e.
			/// C - 	   	Type of the c.
			/// Parameters:
			/// Callback - 	[in,out] If non-null, the callback.
			///-------------------------------------------------------------------------------------------------

			template<class E, class C>
			inline void UnregisterEventCallback(void(C::*Callback)(const E* const))
			{	
				Internal::EventDelegate<C, E> delegate(static_cast<C*>(this), Callback);

				for (auto cb : this->m_RegisteredCallbacks)
				{
					if (cb->GetDelegateId() == delegate.GetDelegateId())
					{
						this->m_RegisteredCallbacks.remove_if(
							[&](const Internal::IEventDelegate* other)
							{
								return other->operator==(cb);
							}
						);

						ECS_Engine->UnsubscribeEvent(&delegate);			
						break;
					}
				}
			}

			void UnregisterAllEventCallbacks();
		};

	} // namespace Event
} // namespace ECS

#endif // __I_EVENT_LISTENER_H__