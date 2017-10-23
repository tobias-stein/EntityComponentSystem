///-------------------------------------------------------------------------------------------------
/// File:	Stash.cpp.
///
/// Summary:	Implements the stash class.
///-------------------------------------------------------------------------------------------------

#include "Stash.h"

#include "ShapeComponent.h"
#include "CollisionComponent2D.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"


Stash::Stash(PlayerId playerId) :
	m_OwningPlayer(playerId),
	m_StashedBounty(0.0f)
{
	Shape shape = ShapeGenerator::CreateShape<QuadShape>();

	AddComponent<ShapeComponent>(shape);
	this->m_ThisMaterial = AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	this->m_ThisRigidbody = AddComponent<RigidbodyComponent>();
	auto cc = AddComponent<CollisionComponent2D>(shape, GetComponent<TransformComponent>()->GetScale(), STASH_COLLSION_CATEGORY, STASH_COLLSION);
	cc->isSensor = true;

	UpdateColor();
}

Stash::~Stash()
{
	this->m_OwningPlayer = INVALID_PLAYER_ID;
	this->m_StashedBounty = 0.0f;
}

void Stash::OnEnable()
{
	UpdateColor();
	this->m_ThisRigidbody->m_Box2DBody->SetActive(true);
}

void Stash::OnDisable()
{
	this->m_ThisRigidbody->m_Box2DBody->SetActive(false);
}

void Stash::StashBounty(float bounty)
{
	if (this->m_StashedBounty + bounty > PLAYER_STASH_SIZE)
	{
		this->m_StashedBounty = PLAYER_STASH_SIZE;
		ECS::ECS_Engine->SendEvent<StashFull>(this->GetEntityID());
	}
	else
	{
		this->m_StashedBounty += bounty;
	}

	UpdateColor();
}

void Stash::UpdateColor()
{
	float alpha = this->m_StashedBounty / PLAYER_STASH_SIZE;
	this->m_ThisMaterial->SetColor(0.0f, 1.0f - alpha, 1.0f);
}