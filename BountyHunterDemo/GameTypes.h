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
using GameObjectId									= ECS::EntityId;
using GameObjectTypeId								= ECS::EntityTypeId;

using PlayerId										= size_t;



static const GameObjectId	INVALID_GAMEOBJECT_ID	{ ECS::INVALID_ENTITY_ID };
static const PlayerId		INVALID_PLAYER_ID		{ std::numeric_limits<PlayerId>::max() };


#endif // __GAME_TYPES_H__
