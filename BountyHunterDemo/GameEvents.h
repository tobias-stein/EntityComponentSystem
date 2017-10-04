///-------------------------------------------------------------------------------------------------
/// File:	GameEvents.h.
///
/// Summary:	Declares the game events.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_EVENTS_H__
#define __GAME_EVENTS_H__

#include <Event/Event.h>

///-------------------------------------------------------------------------------------------------
/// Summary:	General game state events.
/// Author:	Tobias Stein
///
/// Date:	4/10/2017
///-------------------------------------------------------------------------------------------------

struct GameInitializedEvent : public ECS::Event::Event<GameInitializedEvent>
{};

struct GameStartedEvent : public ECS::Event::Event<GameStartedEvent>
{};

struct GamePausedEvent : public ECS::Event::Event<GamePausedEvent>
{};

struct GameResumedEvent : public ECS::Event::Event<GameResumedEvent>
{};

struct GameQuitEvent : public ECS::Event::Event<GameQuitEvent>
{};

struct PauseGameEvent : public ECS::Event::Event<PauseGameEvent>
{};

struct ResumeGameEvent : public ECS::Event::Event<ResumeGameEvent>
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

#endif // __GAME_EVENTS_H__