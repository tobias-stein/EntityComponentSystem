///-------------------------------------------------------------------------------------------------
/// File:	BountyRadar.cpp.
///
/// Summary:	Implements the bounty radar class.
///-------------------------------------------------------------------------------------------------

#include "BountyRadar.h"

#include "RenderSystem.h" // debug drawing

#include "Collector.h"
#include "Bounty.h"

BountyRadar::BountyRadar(float viewDistance, float lineOfSight) :
	m_ViewDistance(viewDistance),
	m_LOS(lineOfSight),
	m_Radar(nullptr)
{
	RegisterEventCallbacks();
}

BountyRadar::~BountyRadar()
{
	UnregisterAllEventCallbacks();
}

void BountyRadar::Initialize()
{
	// setup radar
	{
		RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(this->GetOwner());

		b2FixtureDef radarDef;
		{
			const float STEP = this->m_LOS / 6.0f;
			const float start = glm::half_pi<float>() - (this->m_LOS * 0.5f);

			b2Vec2 vertices[8];
			vertices[0].Set(0, 0);

	
			float c = glm::cos(STEP);
			float s = glm::sin(STEP);
	

			glm::vec2 r1(glm::cos(start), glm::sin(start));
			glm::vec2 v1 = this->m_ViewDistance * r1;

			for (size_t i = 1; i < 8; ++i)
			{
				glm::vec2 r2;

				r2.x = c * r1.x - s * r1.y;
				r2.y = s * r1.x + c * r1.y;

				glm::vec2 v2 = this->m_ViewDistance * r2;

				vertices[i].Set(v1.x, v1.y);

				r1 = r2;
				v1 = v2;
			}
		
			this->m_b2RadarShape.Set(vertices, 8);
			radarDef.shape = &this->m_b2RadarShape;
			radarDef.isSensor = true;
			radarDef.filter.categoryBits = CollisionCategory::BountyRadar_Category;
			radarDef.filter.maskBits = CollisionMask::BountyRadar_Collision;
			radarDef.userData = rbComp;
		}

		this->m_Radar = rbComp->m_Box2DBody->CreateFixture(&radarDef);
	}
}

void BountyRadar::Destroy()
{
	// destroy radar
	{
		RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(this->GetOwner());
		if (rbComp != nullptr && this->m_Radar != nullptr)
		{
			rbComp->m_Box2DBody->DestroyFixture(this->m_Radar);
		}
	}
}

void BountyRadar::DebugDrawRadar()
{
	static RenderSystem* RS = ECS::ECS_Engine->GetSystemManager()->GetSystem<RenderSystem>();

	float angle = this->m_Radar->GetBody()->GetAngle() + glm::half_pi<float>();
	float halfLOS = this->m_LOS * 0.5f;
	auto pos = this->m_Radar->GetBody()->GetPosition();

	RS->DrawSegment(Position2D(pos.x, pos.y), this->m_ViewDistance, angle - halfLOS, angle + halfLOS, Color3f(1.0f, 0.8f, 0.0f));
}


void BountyRadar::RegisterEventCallbacks()
{
	RegisterEventCallback(&BountyRadar::OnCollisionBegin);
	RegisterEventCallback(&BountyRadar::OnCollisionEnd);
}

void BountyRadar::OnCollisionBegin(const CollisionBeginEvent* event)
{
	auto ownerId = this->GetOwner();

	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Bounty::STATIC_ENTITY_TYPE_ID))
	{
		if (event->details.collisionCategoryA == CollisionCategory::BountyRadar_Category)
			RadarAddBountyAction((Collector*)objectA, (Bounty*)objectB);
	}
	else if ((typeA == Bounty::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		if (event->details.collisionCategoryB == CollisionCategory::BountyRadar_Category)
			RadarAddBountyAction((Collector*)objectB, (Bounty*)objectA);
	}
}

void BountyRadar::OnCollisionEnd(const CollisionEndEvent* event)
{
	ECS::IEntity* objectA = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectA);
	ECS::IEntity* objectB = ECS::ECS_Engine->GetEntityManager()->GetEntity(event->objectB);

	GameObjectTypeId typeA = objectA->GetStaticEntityTypeID();
	GameObjectTypeId typeB = objectB->GetStaticEntityTypeID();

	if ((typeA == Collector::STATIC_ENTITY_TYPE_ID) && (typeB == Bounty::STATIC_ENTITY_TYPE_ID))
	{
		if (event->details.collisionCategoryA == CollisionCategory::BountyRadar_Category)
			RadarRemoveBountyAction((Collector*)objectA, (Bounty*)objectB);
	}
	else if ((typeA == Bounty::STATIC_ENTITY_TYPE_ID) && (typeB == Collector::STATIC_ENTITY_TYPE_ID))
	{
		if (event->details.collisionCategoryB == CollisionCategory::BountyRadar_Category)
			RadarRemoveBountyAction((Collector*)objectB, (Bounty*)objectA);
	}
}

void BountyRadar::RadarAddBountyAction(Collector* collector, Bounty* bounty)
{
	if (collector->GetEntityID() == this->GetOwner())
	{
		//SDL_Log("'%d' detected bouty '%d'.", this->GetOwner(), bounty->GetEntityID());
		this->m_DetectedBounty.push_back(bounty);
	}
}

void BountyRadar::RadarRemoveBountyAction(Collector* collector, Bounty* bounty)
{
	if (collector->GetEntityID() == this->GetOwner())
	{
		//SDL_Log("'%d' lost bouty '%d'.", this->GetOwner(), bounty->GetEntityID());
		this->m_DetectedBounty.remove(bounty);
	}
}
