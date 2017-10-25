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
	// change system manager active work state
	ECS::ECS_Engine->GetSystemManager()->SetSystemWorkState(this->m_NotIngame_SystemWSM);

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

	// change system manager active work state
	ECS::ECS_Engine->GetSystemManager()->SetSystemWorkState(this->m_Ingame_SystemWSM);

	ECS::ECS_Engine->SendEvent<GameResumedEvent>();
}