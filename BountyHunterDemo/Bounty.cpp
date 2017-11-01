///-------------------------------------------------------------------------------------------------
/// File:	Bounty.cpp.
///
/// Summary:	Implements the bounty class.
///-------------------------------------------------------------------------------------------------

#include "Bounty.h"

#include "ShapeComponent.h"
#include "RespawnComponent.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"




Bounty::Bounty(GameObjectId spawnId)
{
	Shape shape = ShapeGenerator::CreateShape<QuadShape>();

	AddComponent<ShapeComponent>(shape);
	this->m_ThisMaterial = AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(BOUNTY_RESPAWNTIME, spawnId, true);
	this->m_ThisRigidbody = AddComponent<RigidbodyComponent>(0.0f, 0.0f, 0.0f, 0.0f, 0.0001f);
	this->m_ThisTransform = GetComponent<TransformComponent>();
	this->m_ThisCollision = AddComponent<CollisionComponent2D>(shape, this->m_ThisTransform->GetScale(), CollisionCategory::Bounty_Category, CollisionMask::Bounty_Collision);
	this->m_ThisLifetime = AddComponent<LifetimeComponent>(BOUNTY_MIN_LIFETIME, BOUNTY_MAX_LIFETIME);
}

Bounty::~Bounty()
{
}

void Bounty::OnEnable()
{
	ShuffleBounty();

	this->m_ThisLifetime->ResetLifetime();

	this->m_ThisRigidbody->SetTransform(*this->m_ThisTransform);
	this->m_ThisRigidbody->m_Box2DBody->SetLinearVelocity(b2Vec2_zero);
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(0.0f);
	this->m_ThisRigidbody->m_Box2DBody->SetActive(true);
}

void Bounty::OnDisable()
{
	this->m_ThisRigidbody->m_Box2DBody->SetActive(false);
}

void Bounty::ShuffleBounty()
{
	float alpha = glm::linearRand(0.0f, 1.0f);

	this->m_Value = glm::lerp(MIN_BOUNTY_VALUE, MAX_BOUNTY_VALUE, alpha);

	float scale = glm::lerp(MIN_BOUNTY_SCALE, MAX_BOUNTY_SCALE, alpha);

	this->m_ThisTransform->SetScale(glm::vec3(scale));
	this->m_ThisMaterial->SetColor(1.0f, 1.0f - alpha, 0.0f);
	this->m_ThisRigidbody->SetScale(glm::vec2(scale));
}
