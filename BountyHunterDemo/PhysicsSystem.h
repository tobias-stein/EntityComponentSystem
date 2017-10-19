///-------------------------------------------------------------------------------------------------
/// File:	PhysicsSystem.h.
///
/// Summary:	Declares the physics system class.
///-------------------------------------------------------------------------------------------------

#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

#include <ECS/ECS.h>

#include "Box2D/Dynamics/b2WorldCallbacks.h"

class PhysicsSystem : public ECS::System<PhysicsSystem>, public b2ContactListener
{
public:

	PhysicsSystem();
	virtual ~PhysicsSystem();

	virtual void PreUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void PostUpdate(float dt) override;


	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

}; // class PhysicsSystem

#endif // __PHYSICS_SYSTEM_H__