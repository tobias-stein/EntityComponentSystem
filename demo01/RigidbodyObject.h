#ifndef __RIGIDBODY_OBJECT_H__
#define __RIGIDBODY_OBJECT_H__

#include "ECS.h"

#include "EntityBellowSeaLevelEvent.h"

#include "PositionComponent.h"
#include "RigidbodyComponent.h"

class RigidBodyObject : 
	public ECS::Entity<RigidBodyObject>,
	public ECS::Event::IEventListener
{

public:
	
	RigidBodyObject(Vec3_t& pos, float mass)
	{
		this->AddComponent<PositionComponent>(pos);
		this->AddComponent<RigidBodyComponent>(mass);

		RegisterEventCallback(&RigidBodyObject::OnEntityBellowSeaLevel);

		LogTrace("RigidBodyObject created!");
	}

	~RigidBodyObject()
	{
		LogTrace("RigidBodyObject destroyed!");
	}

	inline void OnEntityBellowSeaLevel(const EntityBellowSeaLevelEvent* const event)
	{
	//	printf("Entity [%d] bellow sea level.\n", this->GetEntityId());

		// diable this enity, if bellow sea level
		this->SetActive(false);
	}
};

#endif // __RIGIDBODY_OBJECT_H__