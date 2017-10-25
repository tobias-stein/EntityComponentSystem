///-------------------------------------------------------------------------------------------------
/// File:	RigidbodyComponent.cpp.
///
/// Summary:	Implements the rigidbody component class.
///-------------------------------------------------------------------------------------------------

#include "RigidbodyComponent.h"
#include "CollisionComponent2D.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

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

void RigidbodyComponent::SetScale(const glm::vec2 & scale)
{
	CollisionComponent2D* CC2D = ECS::ECS_Engine->GetComponentManager()->GetComponent<CollisionComponent2D>(this->GetOwner());
	if (CC2D != nullptr)
	{
		// destroy current fixture
		this->m_Box2DBody->DestroyFixture(this->m_Box2DBody->GetFixtureList());

		// update shape scale
		CC2D->Rescale(scale);

		// create new fixture with new scale
		b2FixtureDef fixtureDef;
		{
			switch (CC2D->shapeType)
			{
			case b2Shape::e_circle:
				fixtureDef.shape = &CC2D->asCircleShape;
				break;

			case b2Shape::e_polygon:
				fixtureDef.shape = &CC2D->asPolygonShape;
				break;

			default:
				assert(false && "Unsupported collision shape!");
			}

			fixtureDef.friction = this->m_Friction;
			fixtureDef.density = this->m_Density;

			fixtureDef.filter.categoryBits = CC2D->collisionCategory;
			fixtureDef.filter.maskBits = CC2D->collisionMask;

			fixtureDef.isSensor = CC2D->isSensor;
		}

		// create new fixture and add reference to its component
		this->m_Box2DBody->CreateFixture(&fixtureDef)->SetUserData(this);
	}
}
