///-------------------------------------------------------------------------------------------------
/// File:	RigidbodyComponent.h.
///
/// Summary:	Declares the rigidbody component class.
///-------------------------------------------------------------------------------------------------

#ifndef __RIGID_BODY_COMPONENT_H__
#define __RIGID_BODY_COMPONENT_H__

#include <ECS/ECS.h>

#include "Transform.h"

#include "Box2D/Dynamics/b2Body.h"

class RigidbodyComponent : public ECS::Component<RigidbodyComponent>
{
public:

	b2BodyType	m_Box2DBodyType;

	float		m_LinearDamping;
	float		m_AngularDamping;
	float		m_Friction;
	float		m_Restitution;

	/// Summary:	The box2D physics body object. This member will be set by World2D class.
	b2Body*		m_Box2DBody;

	RigidbodyComponent();
	RigidbodyComponent(float friction, float restitution, float linearDamping, float angularDamping);
	virtual ~RigidbodyComponent();

	void SetTransform(const Transform& transform);

}; // class RigidbodyComponent

#endif // __RIGID_BODY_COMPONENT_H__