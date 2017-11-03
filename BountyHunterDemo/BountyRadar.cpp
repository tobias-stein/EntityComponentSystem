///-------------------------------------------------------------------------------------------------
/// File:	BountyRadar.cpp.
///
/// Summary:	Implements the bounty radar class.
///-------------------------------------------------------------------------------------------------

#include "BountyRadar.h"

#include "Collector.h"
#include "Bounty.h"

BountyRadar::BountyRadar(float viewDistance, float lineOfSight) :
	m_ViewDistance(viewDistance),
	m_LOS(lineOfSight)
{
	RegisterEventCallbacks();
}

BountyRadar::~BountyRadar()
{
	UnregisterAllEventCallbacks();
}

void BountyRadar::RegisterEventCallbacks()
{
	RegisterEventCallback(&BountyRadar::OnCollisionBegin);
	RegisterEventCallback(&BountyRadar::OnCollisionEnd);
}

void BountyRadar::OnCollisionBegin(const CollisionBeginEvent* event)
{
	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Bounty::STATIC_ENTITY_TYPE_ID))
	{
		RadarAddBountyAction((Collector*)objectA, (Bounty*)objectB);
	}
	else if ((typeA == Bounty::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		RadarAddBountyAction((Collector*)objectB, (Bounty*)objectA);
	}
}

void BountyRadar::OnCollisionEnd(const CollisionEndEvent* event)
{
	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Bounty::STATIC_ENTITY_TYPE_ID))
	{
		RadarRemoveBountyAction((Collector*)objectA, (Bounty*)objectB);
	}
	else if ((typeA == Bounty::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		RadarRemoveBountyAction((Collector*)objectB, (Bounty*)objectA);
	}
}

void BountyRadar::RadarAddBountyAction(Collector* collector, Bounty* bounty)
{
	if (collector->GetEntityID() == this->GetOwner())
	{
		this->m_DetectedBounty.push_back(bounty);
	}
}

void BountyRadar::RadarRemoveBountyAction(Collector* collector, Bounty* bounty)
{
	if (collector->GetEntityID() == this->GetOwner())
	{
		this->m_DetectedBounty.remove(bounty);
	}
}
