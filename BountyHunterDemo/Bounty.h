///-------------------------------------------------------------------------------------------------
/// File:	Bounty.h.
///
/// Summary:	Declares the bounty entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __BOUNTY_ENTITY_H__
#define __BOUNTY_ENTITY_H__

#include "GameObject.h"

#include "ShapeComponent.h"
#include "MaterialComponent.h"
#include "RespawnComponent.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

class Bounty : public GameObject<Bounty>
{
public:

	Bounty(GameObjectId spawnId);
	virtual ~Bounty();

}; // class Bounty

#endif // __BOUNTY_ENTITY_H__
