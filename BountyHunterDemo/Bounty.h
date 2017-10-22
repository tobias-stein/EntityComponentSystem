///-------------------------------------------------------------------------------------------------
/// File:	Bounty.h.
///
/// Summary:	Declares the bounty entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __BOUNTY_ENTITY_H__
#define __BOUNTY_ENTITY_H__

#include "GameObject.h"

#include "RigidbodyComponent.h"
#include "MaterialComponent.h"
#include "CollisionComponent2D.h"
#include "LifetimeComponent.h"

class Bounty : public GameObject<Bounty>, public ECS::Event::IEventListener
{
private:

	TransformComponent*		m_ThisTransform;
	RigidbodyComponent*		m_ThisRigidbody;
	CollisionComponent2D*	m_ThisCollision;
	MaterialComponent*		m_ThisMaterial;
	LifetimeComponent*		m_ThisLifetime;

	float					m_Value;

public:

	Bounty(GameObjectId spawnId);
	virtual ~Bounty();

	virtual void OnEnable() override;
	virtual void OnDisable() override;

	inline float GetBounty() const { return this->m_Value; }

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void Bounty::ShuffleBounty();
	///
	/// Summary:	Shuffle new bounty.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	22/10/2017
	///-------------------------------------------------------------------------------------------------

	void ShuffleBounty();

}; // class Bounty

#endif // __BOUNTY_ENTITY_H__
