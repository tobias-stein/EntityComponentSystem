///-------------------------------------------------------------------------------------------------
/// File:	GameTypes.h.
///
/// Summary:	Declares the game types class.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_TYPES_H__
#define __GAME_TYPES_H__

#include <ECS/ECS.h>
#include <stdint.h>

// allias for entity
using GameObjectId										= ECS::EntityId;
using GameObjectTypeId									= ECS::EntityTypeId;

using PlayerId											= size_t;


static const GameObjectId	INVALID_GAMEOBJECT_ID		{ ECS::INVALID_ENTITY_ID };
static const PlayerId		INVALID_PLAYER_ID			{ std::numeric_limits<PlayerId>::max() };

// Collision categories
static const uint16_t		DEFAULT_COLLSION_CATEGORY	{ 0x0001 };
static const uint16_t		PLAYER_COLLSION_CATEGORY	{ 0x0002 };
static const uint16_t		BOUNTY_COLLSION_CATEGORY	{ 0x0004 };


// Collision rules (masks)
static const uint16_t		DEFAULT_COLLSION			{ 0xffff };
static const uint16_t		PLAYER_COLLSION				{ DEFAULT_COLLSION };
static const uint16_t		BOUNTY_COLLSION				{ DEFAULT_COLLSION ^ BOUNTY_COLLSION_CATEGORY };


/*

Collision Matrix:

D = default
P = player
B = bounty


   | D | P | B
---+---+---+---
 D | x | x | x
---+---+---+---
 P | x | x | x
---+---+---+---
 B | x | x |
---+---+---+---

*/

///-------------------------------------------------------------------------------------------------
/// Enum:	GameState
///
/// Summary:	Values that represent game states.
///-------------------------------------------------------------------------------------------------

enum GameState {

	NOT_INITIALIZED = 0,
	INITIALIZED,
	RESTARTED,
	STARTED,
	RUNNING,
	PAUSED,
	GAMEOVER,
	TERMINATED
}; // enum GameState

#endif // __GAME_TYPES_H__
