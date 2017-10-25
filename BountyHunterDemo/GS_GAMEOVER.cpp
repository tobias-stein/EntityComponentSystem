///-------------------------------------------------------------------------------------------------
/// File:	GS_GAMEOVER.cpp.
///
/// Summary:	Implements the 'GAMEOVER' gamestate.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::GS_GAMEOVER()
{
}

void Game::GS_GAMEOVER_ENTER()
{
	// change system manager active work state
	ECS::ECS_Engine->GetSystemManager()->SetSystemWorkState(this->m_NotIngame_SystemWSM);

	UnregisterEventCallback(&Game::OnPauseGame);
	UnregisterEventCallback(&Game::OnResumeGame);
	UnregisterEventCallback(&Game::OnStashFull);

	RegisterEventCallback(&Game::OnRestartGame);
	RegisterEventCallback(&Game::OnQuitGame);

	ECS::ECS_Engine->SendEvent<GameoverEvent>();

	// print menu options to console
	MenuSystem::PrintMenuOptions();
}

void Game::GS_GAMEOVER_LEAVE()
{
	UnregisterEventCallback(&Game::OnRestartGame);
	UnregisterEventCallback(&Game::OnQuitGame);
}