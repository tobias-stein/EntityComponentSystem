#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__

#include "Vec3.h"
#include "Component.h"

class RigidBodyComponent : public ECS::Component<RigidBodyComponent>
{
	float m_Mass;

	Vec3_t m_Velocity;

	// ...

public:

	RigidBodyComponent(float mass, Vec3_t& initialVelocity = Vec3_t(0, 0, 0)) :
		m_Mass(mass),
		m_Velocity(initialVelocity)
	{}

	virtual ~RigidBodyComponent()
	{}

	// ACCESSORS

	inline void SetMass(float mass)
	{
		this->m_Mass = mass;
	}

	inline float GetMass() const
	{
		return this->m_Mass;
	}

	inline void SetVelocity(Vec3_t& velocity)
	{
		this->m_Velocity = velocity;
	}

	inline const Vec3_t& GetVelocity() const
	{
		return this->m_Velocity;
	}

};

#endif // __RIGIDBODY_COMPONENT_H__