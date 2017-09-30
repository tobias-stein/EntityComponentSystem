#include "stdafx.h"
#include "CppUnitTest.h"


#include "Entity.h"
#include "Event/Event.h"
#include "Event/IEventListener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testEntityComponentSystem
{		


	class DummyEvent : public ECS::Event::Event<DummyEvent>
	{
	public:

		int   m_var1;

		DummyEvent() :
			Event(ECS::INVALID_ENTITY_ID, ECS::INVALID_ENTITY_ID),
			m_var1(123)
		{}
	};


	class Dummy :
		public ECS::Entity<Dummy>,
		public ECS::Event::IEventListener
	{
	public:

		Dummy()
		{
			this->RegisterEventCallback(&Dummy::OnDummyEvent);
		}

		~Dummy()
		{
			//this->UnregisterEventCallback<EntityBellowSeaLevelEvent>();
		}

		inline void OnDummyEvent(const DummyEvent* const event)
		{}
	};

	TEST_CLASS(EventHandlerTest)
	{
	public:
		
		TEST_METHOD(Dispatch_1_Event_5000_Times)
		{
			ECS::Event::EventHandler::GetInstance().ClearEventDispatcher();

			// dummy listener
			Dummy dummy;

			for (int i = 0; i < 5000; ++i)
			{
				ECS::Event::EventHandler::GetInstance().Send<DummyEvent>();
				ECS::Event::EventHandler::GetInstance().DispatchEvents();
			}
		}

		TEST_METHOD(Dispatch_5000_Event_1_Time)
		{
			ECS::Event::EventHandler::GetInstance().ClearEventDispatcher();

			// dummy listener
			Dummy dummy;

			for (int i = 0; i < 5000; ++i)
				ECS::Event::EventHandler::GetInstance().Send<DummyEvent>();

			ECS::Event::EventHandler::GetInstance().DispatchEvents();
		}
	};
}