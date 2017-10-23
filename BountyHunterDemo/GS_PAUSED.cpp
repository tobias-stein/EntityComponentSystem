///-------------------------------------------------------------------------------------------------
/// File:	GS_PAUSED.cpp.
///
/// Summary:	Implements the 'PAUSED' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_PAUSED()
{
}

void Game::GS_PAUSED_ENTER()
{
	ECS::ECS_Engine->SendEvent<GamePausedEvent>();

	RegisterEventCallback(&Game::OnRestartGame);
	RegisterEventCallback(&Game::OnQuitGame);

	// print menu options to console
	MenuSystem::PrintMenuOptions();
}

void Game::GS_PAUSED_LEAVE()
{
	UnregisterEventCallback(&Game::OnRestartGame);
	UnregisterEventCallback(&Game::OnQuitGame);

	ECS::ECS_Engine->SendEvent<GameResumedEvent>();
}