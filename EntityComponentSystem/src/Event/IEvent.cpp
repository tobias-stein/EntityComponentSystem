///-------------------------------------------------------------------------------------------------
/// File:	src\Event\IEvent.cpp.
///
/// Summary:	Declares the IEvent interface.
///-------------------------------------------------------------------------------------------------


#include "Event/IEvent.h"

#include "Engine.h"
#include "util/Timer.h"

namespace ECS { namespace Event {

	IEvent::IEvent(EventTypeId typeId, EntityId sender, EntityId receiver) :
		m_TypeId(typeId),
		m_Sender(sender),
		m_Receiver(receiver)
	{
		assert(ECS_Engine != nullptr && "ECS engine not initialized!");
		this->m_TimeCreated = ECS_Engine->ECS_EngineTime->GetTimeStamp();
	}

}} // namespace ECS::Event
