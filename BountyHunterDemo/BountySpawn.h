///-------------------------------------------------------------------------------------------------
/// File:	BountySpawn.h.
///
/// Summary:	Declares the player spawn class.
///-------------------------------------------------------------------------------------------------

#ifndef __BOUNTY_SPAWN_H__
#define __BOUNTY_SPAWN_H__

#include "GameObjectSpawn.h"

class BountySpawn : public GameObjectSpawn
{
public:

	BountySpawn(const Position& position, const glm::vec2& halfExpand, const float orientation);
	virtual ~BountySpawn();


	// Inherited via GameObjectSpawn
	virtual SpawnInfo GetSpawnInfo() override;

}; // class BountySpawn

#endif // __BOUNTY_SPAWN_H__