#ifndef __RIGIDBODY_OBJECT_H__
#define __RIGIDBODY_OBJECT_H__

#include "Entity.h"

#include "Event/IEventListener.h"

#include "EntityBellowSeaLevelEvent.h"

#include "PositionComponent.h"
#include "RigidbodyComponent.h"

#include "Log/ILogSubscriber.h"

class RigidBodyObject : 
	public ECS::Entity, 
	public ECS::Event::IEventListener,
	public ECS::Log::ILogSubscriber
{
public:

	RigidBodyObject(Vec3_t& pos, float mass) :
		ILogSubscriber("RigidBodyObject")
	{
		this->AddComponent<PositionComponent>(pos);
		this->AddComponent<RigidBodyComponent>(mass);

		this->RegisterEventCallback(&RigidBodyObject::OnEntityBellowSeaLevel);
	}

	~RigidBodyObject()
	{}

	inline void OnEntityBellowSeaLevel(const EntityBellowSeaLevelEvent* const event)
	{
		LogTrace("Entity [%d]: received \'EntityBellowSealevel\' event.", this->GetEntityId());

		// diable this enity, if bellow sea level
		this->SetActive(false);
	}
};

#endif // __RIGIDBODY_OBJECT_H__