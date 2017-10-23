///-------------------------------------------------------------------------------------------------
/// File:	MenuSystem.h.
///
/// Summary:	Declares the menu system class.
///-------------------------------------------------------------------------------------------------

#ifndef __MENU_SYSTEM_H__
#define __MENU_SYSTEM_H__

#include <ECS/ECS.h>

#include "GameEvents.h"


static constexpr size_t MAX_GAME_MENU_OPTIONS	{ 4 };

static constexpr size_t GAME_MENU_OPTION_1		{ 0 };
static constexpr size_t GAME_MENU_OPTION_2		{ 1 };
static constexpr size_t GAME_MENU_OPTION_3		{ 2 };
static constexpr size_t GAME_MENU_OPTION_4		{ 3 };

static const size_t	GAME_MENU_OPTION_COUNT[MAX_GAMESTATES]
{
	0, // 'NOT_INITIALIZED'
	0, // 'INITIALIZED'
	0, // 'RESTARTED'
	0, // 'STARTED'
	0, // 'RUNNING'
	3, // 'PAUSED'
	2, // 'GAMEOVER'
	0, // 'TERMINATED'
};

static IGameMenuOption* GAME_MENU_OPTIONS[MAX_GAMESTATES][MAX_GAME_MENU_OPTIONS]
{
	// 'NOT_INITIALIZED'
	{
	},

	// 'INITIALIZED'
	{
	},

	// 'RESTARTED'
	{
	},

	// 'STARTED'
	{
	},

	// 'RUNNING'
	{
	},

	// 'PAUSED'
	{
		new GameMenuOption<ResumeGameEvent>("Resume Game"),
		new GameMenuOption<RestartGameEvent>("Restart Game"),
		new GameMenuOption<QuitGameEvent>("Quit Game")
	},

	// 'GAMEOVER'
	{
		new GameMenuOption<RestartGameEvent>("Restart Game"),
		new GameMenuOption<QuitGameEvent>("Quit Game")
	},

	// 'TERMINATED'
	{
	},
};

class MenuSystem : public ECS::System<MenuSystem>, protected ECS::Event::IEventListener
{
private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void MenuSystem::OnKeyDownEvent(const KeyDownEvent* event);
	///
	/// Summary:	Processes keys and raises Game specific event like pause, resume, quit.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	4/10/2017
	///
	/// Parameters:
	/// event - 	The event.
	///-------------------------------------------------------------------------------------------------

	void OnKeyDownEvent(const KeyDownEvent* event);

public:

	MenuSystem();
	~MenuSystem();

	static void PrintMenuOptions();

}; // class MenuSystem

#endif // __MENU_SYSTEM_H__
