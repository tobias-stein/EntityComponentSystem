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
		class IEventListener;
		class EventHandler;
	}

	class EntityManager;
	class SystemManager;
	class ComponentManager;



	class ECS_API ECSEngine
	{
		friend class IEntity;
		friend class EntityManager;
		friend class IComponent;
		friend class Event::IEventListener;

	private:

		EntityManager*				ECS_EntityManager;

		ComponentManager*			ECS_ComponentManager;

		SystemManager*				ECS_SystemManager;

		Event::EventHandler*		ECS_EventHandler;


		ECSEngine(const ECSEngine&) = delete;
		ECSEngine& operator=(ECSEngine&) = delete;

		// Add event callback
		template<class E>
		inline void SubscribeEvent(Event::Internal::IEventDelegate* const eventDelegate)
		{
			ECS_EventHandler->AddEventCallback<E>(eventDelegate);
		}

		// Remove event callback
		inline void UnsubscribeEvent(u64 typeId, Event::Internal::EventDelegateId eventDelegateId);

	public:

		ECSEngine();

		~ECSEngine();


		inline EntityManager* GetEntityManager() { return ECS_EntityManager; }

		inline ComponentManager* GetComponentManager() { return ECS_ComponentManager; }

		inline SystemManager* GetSystemManager() { return ECS_SystemManager; }
		
		

		template<class E, class... ARGS>
		void SendEvent(ARGS&&... eventArgs)
		{
			ECS_EventHandler->Send<E>(std::forward<ARGS>(eventArgs)...);
		}


		void Update();
	};

} // namespace ECS

#endif // __ECS_ENGINE_H__