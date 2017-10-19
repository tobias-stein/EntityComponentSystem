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

	void OnGameObjectSpawned(const GameObjectSpawned* event);

public:

	Bounty(GameObjectId spawnId);
	virtual ~Bounty();

}; // class Bounty

#endif // __BOUNTY_ENTITY_H__
