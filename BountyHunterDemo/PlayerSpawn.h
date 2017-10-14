///-------------------------------------------------------------------------------------------------
/// File:	PlayerSpawn.h.
///
/// Summary:	Declares the player spawn class.
///-------------------------------------------------------------------------------------------------

#ifndef __PLAYER_SPAWN_H__
#define __PLAYER_SPAWN_H__

#include "GameObjectSpawn.h"


class PlayerSpawn : public GameObjectSpawn
{
public:

	PlayerSpawn(const Position& position, const float orientation);
	virtual ~PlayerSpawn();


	// Inherited via GameObjectSpawn
	virtual SpawnInfo GetSpawnInfo() override;

}; // class PlayerSpawn

#endif // __PLAYER_SPAWN_H__