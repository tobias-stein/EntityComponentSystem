///-------------------------------------------------------------------------------------------------
/// File:	GameEventHandler.cpp.
///
/// Summary:	Implements the game event handler class.
///-------------------------------------------------------------------------------------------------

#include "Game.h"

void Game::OnPauseGame(const PauseGameEvent* event)
{
	this->PushState(GameState::PAUSED);
}

void Game::OnResumeGame(const ResumeGameEvent* event)
{
	this->PopState();
}

void Game::OnQuitGame(const QuitGameEvent* event)
{
	this->ChangeState(GameState::TERMINATED);
}

void Game::OnToggleFullscreen(const ToggleFullscreenEvent* event)
{
	this->ToggleFullscreen();
}