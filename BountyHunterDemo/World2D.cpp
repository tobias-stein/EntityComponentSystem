///-------------------------------------------------------------------------------------------------
/// File:	World2D.cpp.
///
/// Summary:	Implements the world 2D class.
///-------------------------------------------------------------------------------------------------

#include "World2D.h"
#include "GameConfiguration.h"

#include "PhysicsSystem.h"

#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "CollisionComponent2D.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

World2D::World2D(const Bounds2D& worldBounds, const glm::vec2& worldUp) :
	IWorld(Bounds(Point(worldBounds.minBound, 0.0f), Point(worldBounds.maxBound, 0.0f)), Point(worldUp, 0.0f)),
	m_Box2DWorld(b2Vec2(WORLD_GRAVITY[0], WORLD_GRAVITY[1]))
{
	// Use the PhysicsSystem as contact listener!
	// attention: PhysicsSystem must be create before WorldSystem, which in turn creates this object.
	this->m_Box2DWorld.SetContactListener(ECS::ECS_Engine->GetSystemManager()->GetSystem<PhysicsSystem>());
}

World2D::~World2D()
{}

void World2D::Update(float dt)
{
	this->m_Box2DWorld.Step(dt, PHYSICS_VELOCITY_ITERATIONS, PHYSICS_POSITION_ITERATIONS);
}

void World2D::AddGameObject(GameObjectId gameObjectId)
{
	TransformComponent* tfComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<TransformComponent>(gameObjectId);
	RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(gameObjectId);
	CollisionComponent2D* coComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<CollisionComponent2D>(gameObjectId);

	if (rbComp != nullptr)
	{
		// Create new rigid body
		b2BodyDef bodyDef;
		{
			bodyDef.type = rbComp->m_Box2DBodyType;		
			bodyDef.linearDamping = rbComp->m_LinearDamping;
			bodyDef.angularDamping = rbComp->m_AngularDamping;
		}
		rbComp->m_Box2DBody = this->m_Box2DWorld.CreateBody(&bodyDef);

		// set initial transform
		rbComp->SetTransform(*tfComp);
		
		if (coComp != nullptr)
		{
			b2FixtureDef fixtureDef;
			{
				switch (coComp->shapeType)
				{
					case b2Shape::e_circle:
						fixtureDef.shape = &coComp->asCircleShape;
						break;

					case b2Shape::e_polygon:
						fixtureDef.shape = &coComp->asPolygonShape;
						break;

					default:
						assert(false && "Unsupported collision shape!");
				}

				fixtureDef.friction = rbComp->m_Friction;
				fixtureDef.density = rbComp->m_Density;

				fixtureDef.filter.categoryBits = coComp->collisionCategory;
				fixtureDef.filter.maskBits = coComp->collisionMask;

				fixtureDef.isSensor = coComp->isSensor;
			}

			// create new fixture and add reference to its component
			rbComp->m_Box2DBody->CreateFixture(&fixtureDef)->SetUserData(rbComp);
		}
	}
}

void World2D::RemoveGameObject(GameObjectId gameObjectId)
{
	RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(gameObjectId);
	if (rbComp != nullptr && rbComp->m_Box2DBody != nullptr)
	{
		this->m_Box2DWorld.DestroyBody(rbComp->m_Box2DBody);
		rbComp->m_Box2DBody = nullptr;
	}
}

void World2D::Clear()
{
	b2Body* node = this->m_Box2DWorld.GetBodyList();
	while (node)
	{
		b2Body* b = node;
		node = node->GetNext();

		this->m_Box2DWorld.DestroyBody(b);
	}

	this->m_Box2DWorld.ClearForces();
}

