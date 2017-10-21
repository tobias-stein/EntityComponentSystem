///-------------------------------------------------------------------------------------------------
/// File:	RigidbodyComponent.cpp.
///
/// Summary:	Implements the rigidbody component class.
///-------------------------------------------------------------------------------------------------

#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent() :
	m_Box2DBody(nullptr),
	m_Box2DBodyType(b2BodyType::b2_dynamicBody),
	m_Friction(0.0f),
	m_Restitution(0.0f),
	m_LinearDamping(0.0f),
	m_AngularDamping(0.0f),
	m_Density(1.0f)
{
}

RigidbodyComponent::RigidbodyComponent(float friction, float restitution, float linearDamping, float angularDamping, float density) :
	m_Box2DBody(nullptr),
	m_Box2DBodyType(b2BodyType::b2_dynamicBody),
	m_Friction(friction),
	m_Restitution(restitution),
	m_LinearDamping(linearDamping),
	m_AngularDamping(angularDamping),
	m_Density(density)
{
}

RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::SetTransform(const Transform& transform)
{
	Position2D pos = transform.GetPosition();
	float angle = transform.GetRotation().z;
	this->m_Box2DBody->SetTransform(b2Vec2(pos.x, pos.y), angle);
}
