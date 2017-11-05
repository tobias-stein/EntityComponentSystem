///-------------------------------------------------------------------------------------------------
/// File:	MenuSystem.cpp.
///
/// Summary:	Implements the menu system class.
///-------------------------------------------------------------------------------------------------

#include "MenuSystem.h"
#include "Game.h"

MenuSystem::MenuSystem()
{
	RegisterEventCallbacks();
}

MenuSystem::~MenuSystem()
{
	UnregisterEventCallbacks();
}

void MenuSystem::PrintMenuOptions()
{
	SDL_Log("***** MENU OPTIONS *****\n");
	for (size_t i = 0; i < GAME_MENU_OPTION_COUNT[g_GameInstance->GetActiveGameState()]; ++i)
	{
		SDL_Log("Option #%d - %s\t [\'%d\']\n", i + 1,GAME_MENU_OPTIONS[g_GameInstance->GetActiveGameState()][i]->GetName(), i + 1);
	}
	SDL_Log("***** MENU OPTIONS *****\n");
}

void MenuSystem::RegisterEventCallbacks()
{
	RegisterEventCallback(&MenuSystem::OnKeyDownEvent);
}

void MenuSystem::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&MenuSystem::OnKeyDownEvent);
}

void MenuSystem::OnKeyDownEvent(const KeyDownEvent* event)
{
	switch (event->keyCode)
	{
		// quit game
		case SDLK_ESCAPE:
		case SDLK_q:
			ECS::ECS_Engine->SendEvent<QuitGameEvent>();
			break;

		// pause/resume game
		case SDLK_p:
		{
			static bool s_PAUSED = false;

			if(g_GameInstance->IsPaused() == false)
				ECS::ECS_Engine->SendEvent<PauseGameEvent>();
			else
				ECS::ECS_Engine->SendEvent<ResumeGameEvent>();

			s_PAUSED = !s_PAUSED;
			break;
		}

		// toggle fullscreen
		case SDLK_F1:
			ECS::ECS_Engine->SendEvent<ToggleFullscreenEvent>();
			break;

		// toggle debug draw
		case SDLK_F2:
			ECS::ECS_Engine->SendEvent<ToggleDebugDrawEvent>();
			break;

		//--------------------------------------------
		// GAME 'MENU' OPTIONS
		//--------------------------------------------

		// option 1
		case SDLK_1:
		{
			if (GAME_MENU_OPTION_COUNT[g_GameInstance->GetActiveGameState()] > 0)
				GAME_MENU_OPTIONS[g_GameInstance->GetActiveGameState()][GAME_MENU_OPTION_1]->Execute();
			break;
		}

		// option 2
		case SDLK_2:
		{
			if (GAME_MENU_OPTION_COUNT[g_GameInstance->GetActiveGameState()] > 1)
				GAME_MENU_OPTIONS[g_GameInstance->GetActiveGameState()][GAME_MENU_OPTION_2]->Execute();
			break;
		}

		// option 3
		case SDLK_3:
		{
			if (GAME_MENU_OPTION_COUNT[g_GameInstance->GetActiveGameState()] > 2)
				GAME_MENU_OPTIONS[g_GameInstance->GetActiveGameState()][GAME_MENU_OPTION_3]->Execute();
			break;
		}

		// option 4
		case SDLK_4:
		{
			if (GAME_MENU_OPTION_COUNT[g_GameInstance->GetActiveGameState()] > 3)
				GAME_MENU_OPTIONS[g_GameInstance->GetActiveGameState()][GAME_MENU_OPTION_4]->Execute();
			break;
		}
	}
}