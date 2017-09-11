#ifndef __GRAV_SYS_H__
#define __GRAV_SYS_H__

#include "ECS.h"

#include "Vec3.h"
#include "RigidbodyComponent.h"

// gravity system affects all entities with RigidBodyComponents
class GravitySystem : public ECS::System<GravitySystem>
{
	using RigidBodyComponents = ECS::ComponentList<RigidBodyComponent>;

	// global gravity
	Vec3_t m_G;

	// get access to RigidBodyComponents
	RigidBodyComponents& m_RigidbodyComponents;

public:

	GravitySystem() :
		m_G(0.0f, -9.81f, 0.0f),
		m_RigidbodyComponents(ECS::ECSComponentManager->GetComponentList<RigidBodyComponent>())
	{}

	GravitySystem(Vec3_t g) :
		m_G(g),
		m_RigidbodyComponents(ECS::ECSComponentManager->GetComponentList<RigidBodyComponent>())
	{}

	virtual ~GravitySystem()
	{}

	virtual void Tick(float dt) override
	{
		Vec3_t dtAcceleration(this->m_G.x * dt, this->m_G.y * dt, this->m_G.z * dt);

		for (auto rbComp : this->m_RigidbodyComponents)
		{
			assert(rbComp != nullptr && "Entity has an invalid RigidbodyComponent.");

			// ignore inactive entities
			if (rbComp->GetOwner()->IsActive() == false)
				continue;

			Vec3_t vel = rbComp->GetVelocity();

			// update velocity
			vel.x += dtAcceleration.x;
			vel.y += dtAcceleration.y;
			vel.z += dtAcceleration.z;

			rbComp->SetVelocity(vel);
		}
	}
};

#endif __GRAV_SYS_H__