///-------------------------------------------------------------------------------------------------
/// File:	Bounty.cpp.
///
/// Summary:	Implements the bounty class.
///-------------------------------------------------------------------------------------------------

#include "Bounty.h"

#include "ShapeComponent.h"
#include "MaterialComponent.h"
#include "RespawnComponent.h"
#include "CollisionComponent2D.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"




Bounty::Bounty(GameObjectId spawnId)
{
	Shape shape = ShapeGenerator::CreateShape<QuadShape>();

	AddComponent<ShapeComponent>(shape);
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(BOUNTY_RESPAWNTIME, spawnId, true);
	this->m_ThisRigidbody = AddComponent<RigidbodyComponent>(1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	this->m_ThisTransform = GetComponent<TransformComponent>();

	AddComponent<CollisionComponent2D>(shape, this->m_ThisTransform->GetScale(), BOUNTY_COLLSION_CATEGORY, BOUNTY_COLLSION);
}

Bounty::~Bounty()
{
}

void Bounty::OnEnable()
{
	this->m_ThisRigidbody->SetTransform(*this->m_ThisTransform);
	this->m_ThisRigidbody->m_Box2DBody->SetLinearVelocity(b2Vec2_zero);
	this->m_ThisRigidbody->m_Box2DBody->SetAngularVelocity(0.0f);
	this->m_ThisRigidbody->m_Box2DBody->SetActive(true);
}

void Bounty::OnDisable()
{
	this->m_ThisRigidbody->m_Box2DBody->SetActive(false);
}
