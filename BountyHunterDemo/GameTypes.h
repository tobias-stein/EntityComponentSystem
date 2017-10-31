///-------------------------------------------------------------------------------------------------
/// File:	GameTypes.h.
///
/// Summary:	Declares the game types class.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_TYPES_H__
#define __GAME_TYPES_H__

#include <ECS/ECS.h>
#include <stdint.h>

#include "GameConfiguration.h"

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
static const uint16_t		STASH_COLLSION_CATEGORY		{ 0x0008 };
static const uint16_t		WALL_COLLSION_CATEGORY		{ 0x0010 };

// Collision rules (masks)
static const uint16_t		DEFAULT_COLLSION			{ 0xffff };
static const uint16_t		PLAYER_COLLSION				{ DEFAULT_COLLSION };
static const uint16_t		STASH_COLLSION				{ DEFAULT_COLLSION };
static const uint16_t		BOUNTY_COLLSION				{ DEFAULT_COLLSION ^ (BOUNTY_COLLSION_CATEGORY | STASH_COLLSION_CATEGORY | WALL_COLLSION_CATEGORY) };
static const uint16_t		WALL_COLLSION				{ DEFAULT_COLLSION ^ (WALL_COLLSION_CATEGORY) };

/*

Collision Matrix:

D = default
P = player
B = bounty
S = Stash

   | D | P | B | S | W
---+---+---+---+---+---
 D | x | x | x | x | x
---+---+---+---+---+---
 P | x | x | x | x | x
---+---+---+---+---+---
 B | x | x |   |   | 
---+---+---+---+---+---
 S | x | x |   |   |
---+---+---+---+---+---
 W | x | x |   |   | 
---+---+---+---+---+---
*/

///-------------------------------------------------------------------------------------------------
/// Enum:	GameState
///
/// Summary:	Values that represent game states.
///-------------------------------------------------------------------------------------------------

enum GameState 
{
	NOT_INITIALIZED = 0,
	INITIALIZED,
	RESTARTED,
	STARTED,
	RUNNING,
	PAUSED,
	GAMEOVER,
	TERMINATED,

	MAX_GAMESTATES
}; // enum GameState

static constexpr const char* GameState2String[]
{
	"NOT_INITIALIZED",
	"INITIALIZED",
	"RESTARTED",
	"STARTED",
	"RUNNING",
	"PAUSED",
	"GAMEOVER",
	"TERMINATED",
};

struct GameContext
{
	/// Summary:	The freeze time.
	float	FreezeTime;


	/// Summary:	The play time.
	float	PlayTime;

	GameContext() :
		FreezeTime(DEFAULT_FREEZE_TIME),
		PlayTime(DEFAULT_PLAY_TIME)
	{}

}; // struct GameContext


struct IGameMenuOption
{
	virtual const char* GetName() const = 0;
	virtual void		Execute() = 0;
};

template<class T>
struct GameMenuOption : public IGameMenuOption
{
	const char*			OptionName;

	GameMenuOption(const char* name = nullptr) :
		OptionName(name)
	{}

	virtual const char* GetName() const override { return OptionName; }
	virtual void Execute() override { ECS::ECS_Engine->SendEvent<T>(); }

}; // struct GameMenuOption



#endif // __GAME_TYPES_H__
