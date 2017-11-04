///-------------------------------------------------------------------------------------------------
/// File:	CollectorAvoider.cpp.
///
/// Summary:	Implements the collector avoider class.
///-------------------------------------------------------------------------------------------------

#include "CollectorAvoider.h"

#include "Collector.h"
#include "RenderSystem.h" // debug draw

CollectorAvoider::CollectorAvoider(float viewDistance, float width) :
	m_ViewDistance(viewDistance),
	m_Width(width),
	m_Avoider(nullptr)
{
	RegisterEventCallbacks();
}

CollectorAvoider::~CollectorAvoider()
{
	UnregisterAllEventCallbacks();
}

void CollectorAvoider::RegisterEventCallbacks()
{
	RegisterEventCallback(&CollectorAvoider::OnCollisionBegin);
	RegisterEventCallback(&CollectorAvoider::OnCollisionEnd);
}

void CollectorAvoider::OnCollisionBegin(const CollisionBeginEvent * event)
{
	auto ownerId = this->GetOwner();

	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		if (event->details.collisionCategoryA == CollisionCategory::ObstacleAvoider_Category && event->details.collisionCategoryB == CollisionCategory::Player_Category)
		{
			if (objectA->GetEntityID() == ownerId)
			{
				SDL_Log("'%d' detected obstacle '%d'.", ownerId, objectB->GetEntityID());
				this->m_DetectedCollector.push_back((Collector*)objectB);
			}
		}
		else if (event->details.collisionCategoryA == CollisionCategory::Player_Category && event->details.collisionCategoryB == CollisionCategory::ObstacleAvoider_Category)
		{
			if (objectB->GetEntityID() == ownerId)
			{
				SDL_Log("'%d' detected obstacle '%d'.", ownerId, objectA->GetEntityID());
				this->m_DetectedCollector.push_back((Collector*)objectA);
			}
		}
	}
}

void CollectorAvoider::OnCollisionEnd(const CollisionEndEvent * event)
{
	auto ownerId = this->GetOwner();

	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		if (event->details.collisionCategoryA == CollisionCategory::ObstacleAvoider_Category && event->details.collisionCategoryB == CollisionCategory::Player_Category)
		{
			if (objectA->GetEntityID() == ownerId)
			{
				//SDL_Log("'%d' lost obstacle '%d'.", ownerId, objectB->GetEntityID());
				this->m_DetectedCollector.remove((Collector*)objectB);
			}
		}
		else if (event->details.collisionCategoryA == CollisionCategory::Player_Category && event->details.collisionCategoryB == CollisionCategory::ObstacleAvoider_Category)
		{
			if (objectB->GetEntityID() == ownerId)
			{
				//SDL_Log("'%d' lost obstacle '%d'.", ownerId, objectA->GetEntityID());
				this->m_DetectedCollector.remove((Collector*)objectA);
			}
		}
	}
}



void CollectorAvoider::Initialize()
{
	// setup radar
	{
		RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(this->GetOwner());

		b2FixtureDef avoiderFixDef;
		{
			float halfView = this->m_ViewDistance * 0.5f;
			this->m_b2AvoiderShape.SetAsBox(this->m_Width, halfView, b2Vec2(0.0f, halfView), 0.0f);

			avoiderFixDef.shape = &this->m_b2AvoiderShape;
			avoiderFixDef.isSensor = true;
			avoiderFixDef.filter.categoryBits = CollisionCategory::ObstacleAvoider_Category;
			avoiderFixDef.filter.maskBits = CollisionMask::ObstacleAvoide_Collisionr;
			avoiderFixDef.userData = rbComp;
		}

		this->m_Avoider = rbComp->m_Box2DBody->CreateFixture(&avoiderFixDef);
	}
}

void CollectorAvoider::Destroy()
{
	// destroy radar
	{
		RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(this->GetOwner());
		if (rbComp != nullptr && this->m_Avoider != nullptr)
		{
			rbComp->m_Box2DBody->DestroyFixture(this->m_Avoider);
		}
	}
}

void CollectorAvoider::DebugDrawAvoider()
{
	static RenderSystem* RS = ECS::ECS_Engine->GetSystemManager()->GetSystem<RenderSystem>();

	float angle = this->m_Avoider->GetBody()->GetAngle() + glm::half_pi<float>();
	auto pos = this->m_Avoider->GetBody()->GetPosition();

	glm::vec2 F(glm::cos(angle), glm::sin(angle));
	glm::vec2 S(-F.y, F.x);

	F *= this->m_ViewDistance;
	S *= this->m_Width;

	Position2D P = Position2D(pos.x, pos.y);

	RS->DrawLine(P + S, P + S + F, false, false, Color3f(1.0f, 0.3f, 0.0f));
	RS->DrawLine(P - S, P - S + F, false, false, Color3f(1.0f, 0.3f, 0.0f));
	RS->DrawLine(P - S + F, P + S + F, false, false, Color3f(1.0f, 0.3f, 0.0f));
}
