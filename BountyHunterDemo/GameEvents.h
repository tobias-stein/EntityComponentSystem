///-------------------------------------------------------------------------------------------------
/// File:	GameEvents.h.
///
/// Summary:	Declares the game events.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_EVENTS_H__
#define __GAME_EVENTS_H__

#include <ECS/ECS.h>

#include "GameTypes.h"

#include "Transform.h"

///-------------------------------------------------------------------------------------------------
/// Summary:	General game state events.
/// Author:	Tobias Stein
///
/// Date:	4/10/2017
///-------------------------------------------------------------------------------------------------

struct GameInitializedEvent : public ECS::Event::Event<GameInitializedEvent>
{};

struct GameRestartedEvent : public ECS::Event::Event<GameRestartedEvent>
{};

struct GameStartedEvent : public ECS::Event::Event<GameStartedEvent>
{};

struct GamePausedEvent : public ECS::Event::Event<GamePausedEvent>
{};

struct GameResumedEvent : public ECS::Event::Event<GameResumedEvent>
{};

struct GameoverEvent : public ECS::Event::Event<GameoverEvent>
{};

struct GameQuitEvent : public ECS::Event::Event<GameQuitEvent>
{};

struct PauseGameEvent : public ECS::Event::Event<PauseGameEvent>
{};

struct ResumeGameEvent : public ECS::Event::Event<ResumeGameEvent>
{};

struct RestartGameEvent : public ECS::Event::Event<RestartGameEvent>
{};

struct QuitGameEvent : public ECS::Event::Event<QuitGameEvent>
{};

///-------------------------------------------------------------------------------------------------
/// Summary:	General input events.
/// Author:	Tobias Stein
///
/// Date:	4/10/2017
///-------------------------------------------------------------------------------------------------

#include <SDL_keycode.h>

struct LeftButtonDownEvent : public ECS::Event::Event<LeftButtonDownEvent>
{
	int x;
	int y;

	LeftButtonDownEvent(int x, int y) : x(x), y(y)
	{}
};

struct LeftButtonUpEvent : public ECS::Event::Event<LeftButtonUpEvent>
{
	int x;
	int y;

	LeftButtonUpEvent(int x, int y) : x(x), y(y)
	{}
};

struct LeftButtonPressedEvent : public ECS::Event::Event<LeftButtonPressedEvent>
{
	int x;
	int y;

	LeftButtonPressedEvent(int x, int y) : x(x), y(y)
	{}
};

struct RightButtonDownEvent : public ECS::Event::Event<RightButtonDownEvent>
{
	int x;
	int y;

	RightButtonDownEvent(int x, int y) : x(x), y(y)
	{}
};

struct RightButtonUpEvent : public ECS::Event::Event<RightButtonUpEvent>
{
	int x;
	int y;

	RightButtonUpEvent(int x, int y) : x(x), y(y)
	{}
};

struct RightButtonPressedEvent : public ECS::Event::Event<RightButtonPressedEvent>
{
	int x;
	int y;

	RightButtonPressedEvent(int x, int y) : x(x), y(y)
	{}
};


struct KeyDownEvent : public ECS::Event::Event<KeyDownEvent>
{
	SDL_Keycode keyCode;

	KeyDownEvent(SDL_Keycode key) : keyCode(key)
	{}
};

struct KeyUpEvent : public ECS::Event::Event<KeyUpEvent>
{
	SDL_Keycode keyCode;

	KeyUpEvent(SDL_Keycode code) : keyCode(code)
	{}
};

struct KeyPressedEvent : public ECS::Event::Event<KeyPressedEvent>
{
	SDL_Keycode keyCode;

	KeyPressedEvent(SDL_Keycode code) : keyCode(code)
	{}
};


///-------------------------------------------------------------------------------------------------
/// Summary:	General video state events.
/// Author:	Tobias Stein
///
/// Date:	4/10/2017
///-------------------------------------------------------------------------------------------------

struct ToggleFullscreenEvent : public ECS::Event::Event<ToggleFullscreenEvent>
{};

struct EnterFullscreenModeEvent : public ECS::Event::Event<EnterFullscreenModeEvent>
{};

struct EnterWindowModeEvent : public ECS::Event::Event<EnterWindowModeEvent>
{};


///-------------------------------------------------------------------------------------------------
/// Summary:	Game Object events.
/// Author:	Tobias Stein
///
/// Date:	12/10/2017
///-------------------------------------------------------------------------------------------------

struct GameObjectCreated : public ECS::Event::Event<GameObjectCreated>
{
	GameObjectId		m_EntityID;
	GameObjectTypeId	m_EntityTypeID;

	GameObjectCreated(GameObjectId id, GameObjectTypeId typeId) : 
		m_EntityID(id),
		m_EntityTypeID(typeId)
	{}
};

struct GameObjectDestroyed : public ECS::Event::Event<GameObjectDestroyed>
{
	GameObjectId		m_EntityID;
	GameObjectTypeId	m_EntityTypeID;

	GameObjectDestroyed(GameObjectId id, GameObjectTypeId typeId) :
		m_EntityID(id),
		m_EntityTypeID(typeId)
	{}
};

struct GameObjectSpawned : public ECS::Event::Event<GameObjectSpawned>
{
	GameObjectId	m_EntityID;
	Transform		m_Transform;

	GameObjectSpawned(GameObjectId id, const Transform& transform) :
		m_EntityID(id),
		m_Transform(transform)
	{}
};

struct GameObjectKilled : public ECS::Event::Event<GameObjectKilled>
{
	GameObjectId	m_EntityID;

	GameObjectKilled(GameObjectId id) : m_EntityID(id)
	{}
};

///-------------------------------------------------------------------------------------------------
/// Summary:	Game Camera events.
/// Author:	Tobias Stein
///
/// Date:	9/10/2017
///-------------------------------------------------------------------------------------------------

struct CameraCreated : public ECS::Event::Event<CameraCreated>
{
	GameObjectId cameraID;

	CameraCreated(GameObjectId id) : cameraID(id)
	{}
};

struct CameraDestroyed : public ECS::Event::Event<CameraDestroyed>
{
	GameObjectId cameraID;

	CameraDestroyed(GameObjectId id) : cameraID(id)
	{}
};


///-------------------------------------------------------------------------------------------------
/// Summary:	General window events.
/// Author:	Tobias Stein
///
/// Date:	5/10/2017
///-------------------------------------------------------------------------------------------------

struct WindowMinimizedEvent : public ECS::Event::Event<WindowMinimizedEvent>
{};

struct WindowRestoredEvent : public ECS::Event::Event<WindowRestoredEvent>
{};

struct WindowResizedEvent : public ECS::Event::Event<WindowResizedEvent>
{
	int width;
	int height;

	WindowResizedEvent(int w, int h) :
		width(w),
		height(h)
	{}
};


///-------------------------------------------------------------------------------------------------
/// Summary:	Game events.
/// Author:	Tobias Stein
///
/// Date:	15/10/2017
///-------------------------------------------------------------------------------------------------
 
struct PlayerJoined : public ECS::Event::Event<PlayerJoined>
{
	PlayerId playerID;

	PlayerJoined(PlayerId id) : playerID(id)
	{}
};

struct PlayerLeft : public ECS::Event::Event<PlayerLeft>
{
	PlayerId playerID;

	PlayerLeft(PlayerId id) : playerID(id)
	{}
};


struct StashFull : public ECS::Event::Event<StashFull>
{
	GameObjectId stashId;

	StashFull(GameObjectId id) : stashId(id)
	{}
};


///-------------------------------------------------------------------------------------------------
/// Summary:	Collision events.
/// Author:	Tobias Stein
///
/// Date:	21/10/2017
///-------------------------------------------------------------------------------------------------

struct CollisionBeginEvent : public ECS::Event::Event<CollisionBeginEvent>
{
	GameObjectId objectA;
	GameObjectId objectB;

	struct collisionDetails
	{
		CollisionCategory collisionCategoryA;
		CollisionCategory collisionCategoryB;

		CollisionMask collisionMaskA;
		CollisionMask collisionMaskB;
	} details;

	CollisionBeginEvent(GameObjectId a, GameObjectId b) : objectA(a), objectB(b)
	{}

}; // struct CollisionBeginEvent

struct CollisionEndEvent : public ECS::Event::Event<CollisionEndEvent>
{
	GameObjectId objectA;
	GameObjectId objectB;

	struct collisionDetails
	{
		CollisionCategory collisionCategoryA;
		CollisionCategory collisionCategoryB;

		CollisionMask collisionMaskA;
		CollisionMask collisionMaskB;
	} details;

	CollisionEndEvent(GameObjectId a, GameObjectId b) : objectA(a), objectB(b)
	{}

}; // struct CollisionEndEvent


///-------------------------------------------------------------------------------------------------
/// Summary:	Debug events.
/// Author:	Tobias Stein
///
/// Date:	05/11/2017
///-------------------------------------------------------------------------------------------------

struct ToggleDebugDrawEvent : public ECS::Event::Event<ToggleDebugDrawEvent>
{};

#endif // __GAME_EVENTS_H__