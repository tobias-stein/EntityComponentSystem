///-------------------------------------------------------------------------------------------------
/// File:	GameCamera.cpp.
///
/// Summary:	Implements the game camera class.
///-------------------------------------------------------------------------------------------------

#include "GameCamera.h"


void GameCamera::RegisterEventCallbacks()
{
	RegisterEventCallback(&GameCamera::OnWindowResized);
}

void GameCamera::UnregisterEventCallbacks()
{
	UnregisterEventCallback(&GameCamera::OnWindowResized);
}

void GameCamera::OnWindowResized(const WindowResizedEvent* event)
{
	this->SetViewport(0, 0, event->width, event->height);
}
