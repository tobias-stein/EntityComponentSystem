///-------------------------------------------------------------------------------------------------
/// File:	include\Engine.h.
///
/// Summary:	Declares the engine class.
///-------------------------------------------------------------------------------------------------

#ifndef __ECS_ENGINE_H__
#define __ECS_ENGINE_H__

#include "API.h"

#include "Event/EventDelegate.h"

namespace ECS
{
	namespace Event
	{
		class EventHandler;
	}

	class EntityManager;
	class SystemManager;
	class ComponentManager;



	class ECS_API ECSEngine
	{
		friend class IEntity;

	private:

		EntityManager*				ECS_EntityManager;

		ComponentManager*			ECS_ComponentManager;

		SystemManager*				ECS_SystemManager;

		Event::EventHandler*		ECS_EventHandler;


		ECSEngine(const ECSEngine&) = delete;
		ECSEngine& operator=(ECSEngine&) = delete;

	public:

		ECSEngine();

		~ECSEngine();


		inline EntityManager* GetEntityManager() { return ECS_EntityManager; }

		inline ComponentManager* GetComponentManager() { return ECS_ComponentManager; }

		inline SystemManager* GetSystemManager() { return ECS_SystemManager; }
		
		// Add event callback
		template<class E>
		inline void SubscribeEvent(Event::Internal::IEventDelegate* const eventDelegate)
		{
			ECS_EventHandler->AddEventCallback<E>(eventDelegate);
		}

		// Remove event callback
		template<class E>
		static inline void UnsubscribeEvent(Event::Internal::EventDelegateId eventDelegateId)
		{
			ECS_EventHandler->RemoveEventCallback<E>(eventDelegateId);
		}

		template<class E, class... ARGS>
		void SendEvent(ARGS&&... eventArgs)
		{
			ECS_EventHandler->Send<E>(std::forward<ARGS>(eventArgs)...);
		}


		void Update();
	};

} // namespace ECS

#endif // __ECS_ENGINE_H__