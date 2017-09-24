#ifndef __GRAV_SYS_H__
#define __GRAV_SYS_H__

#include "ECS.h"

#include "Vec3.h"
#include "RigidbodyComponent.h"

// gravity system affects all entities with RigidBodyComponents
class GravitySystem : public ECS::System<GravitySystem>
{
	// global gravity
	Vec3_t m_G;
public:

	GravitySystem() :
		m_G(0.0f, -9.81f, 0.0f)
	{}

	GravitySystem(Vec3_t g) :
		m_G(g)
	{}

	virtual ~GravitySystem()
	{}

	virtual void Tick(float dt) override
	{
		Vec3_t dtAcceleration(this->m_G.x * dt, this->m_G.y * dt, this->m_G.z * dt);

		for (auto it = ECS::ECS_Engine->GetComponentManager()->begin<RigidBodyComponent>(); it != ECS::ECS_Engine->GetComponentManager()->end<RigidBodyComponent>(); ++it)
		{
			//assert(it != nullptr && "Entity has an invalid RigidbodyComponent.");

			// ignore inactive entities
			if (it->GetOwner()->IsActive() == false)
				continue;

			Vec3_t vel = it->GetVelocity();

			// update velocity
			vel.x += dtAcceleration.x;
			vel.y += dtAcceleration.y;
			vel.z += dtAcceleration.z;

			it->SetVelocity(vel);
		}
	}
};

#endif __GRAV_SYS_H__