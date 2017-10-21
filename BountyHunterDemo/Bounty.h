///-------------------------------------------------------------------------------------------------
/// File:	Bounty.h.
///
/// Summary:	Declares the bounty entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __BOUNTY_ENTITY_H__
#define __BOUNTY_ENTITY_H__

#include "GameObject.h"

#include "RigidbodyComponent.h"

class Bounty : public GameObject<Bounty>, public ECS::Event::IEventListener
{
private:

	TransformComponent*		m_ThisTransform;
	RigidbodyComponent*		m_ThisRigidbody;
	
public:

	Bounty(GameObjectId spawnId);
	virtual ~Bounty();

	virtual void OnEnable() override;
	virtual void OnDisable() override;

}; // class Bounty

#endif // __BOUNTY_ENTITY_H__
