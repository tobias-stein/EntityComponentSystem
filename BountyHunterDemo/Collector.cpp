///-------------------------------------------------------------------------------------------------
/// File:	Collector.cpp.
///
/// Summary:	Implements the collector class.
///-------------------------------------------------------------------------------------------------

#include "Collector.h"

#include "ShapeComponent.h"
#include "RespawnComponent.h"
#include "CollisionComponent2D.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

Collector::Collector(GameObjectId spawnId) :
	m_PlayerId(INVALID_PLAYER_ID),
	m_CollectedBounty(0.0f)
{
	Shape shape = ShapeGenerator::CreateShape<TriangleShape>();

	AddComponent<ShapeComponent>(shape);
	this->m_ThisMaterial = AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(COLLECTOR_RESPAWNTIME, spawnId, true);	
	this->m_ThisTransform = GetComponent<TransformComponent>();
	this->m_ThisRigidbody = AddComponent<RigidbodyComponent>();
	AddComponent<CollisionComponent2D>(shape, this->m_ThisTransform->GetScale(), PLAYER_COLLSION_CATEGORY, PLAYER_COLLSION);

	UpdateColor();
}

Collector::~Collector()
{
}



void Collector::OnEnable()
{
	UpdateColor();

	this->m_ThisRigidbody->SetTransform(*this->m_ThisTransform);
	this->m_ThisRigidbody->m_Box2DBody->SetLinearVelocity(b2Vec2_zero);
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(0.0f);
	this->m_ThisRigidbody->m_Box2DBody->SetActive(true);
}

void Collector::OnDisable()
{
	this->m_ThisRigidbody->m_Box2DBody->SetActive(false);
}


void Collector::MoveForward(float speed)
{
	glm::vec2 vel = this->m_ThisTransform->GetUp() * speed;
	this->m_ThisRigidbody->m_Box2DBody->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}

void Collector::TurnLeft(float degrees_sec)
{
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(degrees_sec);
}

void Collector::TurnRight(float degrees_sec)
{
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(-degrees_sec);
}

void Collector::Stop()
{
	this->m_ThisRigidbody->m_Box2DBody->SetLinearVelocity(b2Vec2_zero);
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(0.0f);
}

void Collector::StopTurning()
{
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(0.0f);
}

void Collector::StopMoving()
{
	this->m_ThisRigidbody->m_Box2DBody->SetLinearVelocity(b2Vec2_zero);
}

void Collector::ResetCollectedBounty()
{
	this->m_CollectedBounty = 0.0f;
	UpdateColor();
}

void Collector::CollectBounty(float bounty)
{
	this->m_CollectedBounty = glm::min<float>(this->m_CollectedBounty + bounty, PLAYER_POCKET_SIZE);
	UpdateColor();
}

void Collector::UpdateColor()
{
	float alpha = this->m_CollectedBounty / PLAYER_POCKET_SIZE;
	this->m_ThisMaterial->SetColor(1.0f - alpha, 0.0f, 1.0f);
}