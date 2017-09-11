///-------------------------------------------------------------------------------------------------
/// File:	PositionSystem.h.
///
/// Summary:	Declares the position system class.

#ifndef __POS_SYS_H__
#define __POS_SYS_H__

#include "ECS.h"

#include "Vec3.h"

#include "PositionComponent.h"
#include "RigidbodyComponent.h"

#include "EntityBellowSeaLevelEvent.h"

///-------------------------------------------------------------------------------------------------
/// Class:	PositionSystem
///
/// Summary:	A position system.
///
/// Author:	Tobias Stein
///
/// Date:	9/09/2017

class PositionSystem : public ECS::System<PositionSystem>
{

private:

	using PositionComponents = ECS::ComponentList<PositionComponent>;

	// access to all position components
	PositionComponents& m_PositionComponents;

public:
	
	PositionSystem() :       
		m_PositionComponents(ECS::ECSComponentManager->GetComponentList<PositionComponent>())
	{}

	virtual ~PositionSystem()
	{
	}

	virtual void Tick(float dt) override
	{
		for (auto posComp : this->m_PositionComponents)
		{

			assert(posComp != nullptr && "Entity has an invalid PositionComponent.");

			// ignore inactive entities
			if (posComp->GetOwner()->IsActive() == false)
				continue;

			// Check if entity has RigidBodyComponent
			RigidBodyComponent* rbComp = posComp->GetOwner()->GetComponent<RigidBodyComponent>();
			if (rbComp != nullptr)
			{
				Position3d pos = posComp->GetPosition();
				
				Vec3_t vel = rbComp->GetVelocity();

				pos.x += vel.x * dt;
				pos.y += vel.y * dt;
				pos.z += vel.z * dt;

				posComp->SetPosition(pos);

				// check if entity is bellow sea level
				if (pos.y < 0.0f)
				{
					//m_Logger->LogTrace("Entity [%d] is bellow sea level.", posComp->GetOwner()->GetEntityId());
					LogTrace("Entity [%d] is bellow sea level.", posComp->GetOwner()->GetEntityId());
					ECS::ECSEventHandler->Send<EntityBellowSeaLevelEvent>(posComp->GetOwner()->GetEntityId(), pos.y);
				}
			}
		}
	}
};

#endif // __POS_SYS_H__