///-------------------------------------------------------------------------------------------------
/// File:	PhysicsSystem.cpp.
///
/// Summary:	Implements the physics system class.
///-------------------------------------------------------------------------------------------------

#include "PhysicsSystem.h"
#include "GameEvents.h"

#include "Box2D/Box2D.h"

#include "TransformComponent.h"
#include "RigidbodyComponent.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::PreUpdate(float dt)
{
	// Sync physics rigidbody transformation and TransformComponent
	for (auto RB = ECS::ECS_Engine->GetComponentManager()->begin<RigidbodyComponent>(); RB != ECS::ECS_Engine->GetComponentManager()->end<RigidbodyComponent>(); ++RB)
	{
		if ((RB->m_Box2DBody->IsAwake() == true) && (RB->m_Box2DBody->IsActive() == true))
		{
			TransformComponent* TFC = ECS::ECS_Engine->GetComponentManager()->GetComponent<TransformComponent>(RB->GetOwner());

			const b2Vec2& pos = RB->m_Box2DBody->GetPosition();
			const float   rot = RB->m_Box2DBody->GetAngle();
	
			TFC->SetTransform(glm::translate(glm::mat4(1.0f), Position(pos.x, pos.y, 0.0f)) * glm::yawPitchRoll(0.0f, 0.0f, rot) * glm::scale(TFC->AsTransform()->GetScale()));
		}
	}
}

void PhysicsSystem::Update(float dt)
{
}

void PhysicsSystem::PostUpdate(float dt)
{
}

void PhysicsSystem::BeginContact(b2Contact* contact)
{
	GameObjectId A = ((RigidbodyComponent*)contact->GetFixtureA()->GetUserData())->GetOwner();
	GameObjectId B = ((RigidbodyComponent*)contact->GetFixtureB()->GetUserData())->GetOwner();

	CollisionBeginEvent event(A, B);
	event.details.collisionCategoryA = (CollisionCategory)contact->GetFixtureA()->GetFilterData().categoryBits;
	event.details.collisionCategoryB = (CollisionCategory)contact->GetFixtureB()->GetFilterData().categoryBits;
	event.details.collisionMaskA = (CollisionMask)contact->GetFixtureA()->GetFilterData().maskBits;
	event.details.collisionMaskB = (CollisionMask)contact->GetFixtureB()->GetFilterData().maskBits;

	ECS::ECS_Engine->SendEvent<CollisionBeginEvent>(event);
}

void PhysicsSystem::EndContact(b2Contact* contact)
{
	GameObjectId A = ((RigidbodyComponent*)contact->GetFixtureA()->GetUserData())->GetOwner();
	GameObjectId B = ((RigidbodyComponent*)contact->GetFixtureB()->GetUserData())->GetOwner();

	CollisionEndEvent event(A, B);
	event.details.collisionCategoryA = (CollisionCategory)contact->GetFixtureA()->GetFilterData().categoryBits;
	event.details.collisionCategoryB = (CollisionCategory)contact->GetFixtureB()->GetFilterData().categoryBits;
	event.details.collisionMaskA = (CollisionMask)contact->GetFixtureA()->GetFilterData().maskBits;
	event.details.collisionMaskB = (CollisionMask)contact->GetFixtureB()->GetFilterData().maskBits;

	ECS::ECS_Engine->SendEvent<CollisionEndEvent>(event);
}
