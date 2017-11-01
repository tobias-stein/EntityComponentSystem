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


/*

	Collision Matrix:

	D = default
	P = player
	B = bounty
	S = Stash
	W = Wall
	R = Bounty Radar
	O = Obstacle Avoider

	   | D | P | B | S | W | R | O
	---+---+---+---+---+---+---+---
	 D | x | x | x | x | x |   |
	---+---+---+---+---+---+---+---
	 P | x | x | x | x | x |   | x
	---+---+---+---+---+---+---+---
	 B | x | x |   |   |   | x |
	---+---+---+---+---+---+---+---
	 S | x | x |   |   |   |   |
	---+---+---+---+---+---+---+---
	 W | x | x |   |   |   |   | 
	---+---+---+---+---+---+---+---
	 R |   |   | x |   |   |   | 
	---+---+---+---+---+---+---+---
	 O |   | x |   |   |   |   | 
	---+---+---+---+---+---+---+---

*/

enum CollisionCategory
{
	Default_Category				= 0x0001,
	Player_Category					= 0x0002,
	Bounty_Category					= 0x0004,
	Stash_Category					= 0x0008,
	Wall_Category					= 0x0010,
	BountyRadar_Category			= 0x0020,
	ObstacleAvoider_Category		= 0x0040

}; // enum CollistionCategory

enum CollisionMask
{
	Default_Collision				= 0xffff,
	Player_Collision				= CollisionMask::Default_Collision,
	Bounty_Collision				= (CollisionMask::Default_Collision ^ (CollisionCategory::Bounty_Category | CollisionCategory::Stash_Category | CollisionCategory::Wall_Category)),
	Stash_Collision					= CollisionMask::Default_Collision,
	Wall_Collision					= (CollisionMask::Default_Collision ^ (CollisionCategory::Wall_Category)),
	BountyRadar_Collision			= CollisionCategory::Bounty_Category,
	ObstacleAvoide_Collisionr		= CollisionCategory::Player_Category
	
}; // enum CollisionMask

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
