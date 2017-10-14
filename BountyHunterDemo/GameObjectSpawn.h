///-------------------------------------------------------------------------------------------------
/// File:	GameObjectSpawn.h.
///
/// Summary:	Declares the game object spawn class.
///-------------------------------------------------------------------------------------------------


#ifndef __GAME_OBJECT_SPAWN_H__
#define __GAME_OBJECT_SPAWN_H__

#include "GameObject.h"
#include "SpawnComponent.h"

#ifdef DEBUG_SHOW_SPAWNS
#include "ShapeComponent.h"
#include "MaterialComponent.h"
#include "ShapeGenerator.h"
#include "MaterialGenerator.h"
#endif // DEBUG_SHOW_SPAWNS

class GameObjectSpawn : public GameObject<GameObjectSpawn>
{
public:

	virtual SpawnInfo GetSpawnInfo() = 0;

}; // class GameObjectSpawn

#endif // __GAME_OBJECT_SPAWN_H__
