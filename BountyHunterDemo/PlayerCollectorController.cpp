///-------------------------------------------------------------------------------------------------
/// File:	PlayerCollectorController.cpp.
///
/// Summary:	Implements the player collector controller class.
///-------------------------------------------------------------------------------------------------

#include "PlayerCollectorController.h"



PlayerCollectorController::PlayerCollectorController(const GameObjectId collectorId, const PlayerId playerId) : PlayerController(collectorId),
	m_MoveForward(0),
	m_TurnLeft(0),
	m_TurnRight(0)
{
	this->m_Pawn->SetPlayer(playerId);
}

PlayerCollectorController::~PlayerCollectorController()
{
}


void PlayerCollectorController::Update(float dt)
{
	if (this->m_Pawn->IsActive() == false)
		return;

	// note: we do note scale move and turn speed by dt, the physics engine is taking care of that
	if (this->m_MoveForward == true)
	{
		// move collector at max speed
		this->m_Pawn->MoveForward(COLLECTOR_MAX_MOVE_SPEED);
	}
	else
	{
		this->m_Pawn->StopMoving();
	}

	if (this->m_TurnLeft == true)
	{
		// turn collector at max speed
		this->m_Pawn->TurnLeft(COLLECTOR_MAX_TURN_SPEED);
	}
	else if (this->m_TurnRight == true)
	{
		// turn collector at max speed
		this->m_Pawn->TurnRight(COLLECTOR_MAX_TURN_SPEED);
	}
	else
	{
		this->m_Pawn->StopTurning();
	}
}

void PlayerCollectorController::OnKeyDown(const KeyDownEvent* event)
{
	switch (event->keyCode)
	{
		// Move Forawrd
		case SDLK_UP:
		case SDLK_w:
		{
			this->m_MoveForward = true;
			break;
		}

		// Turn Left
		case SDLK_LEFT:
		case SDLK_a:
		{
			this->m_TurnLeft = true;
			this->m_TurnRight = false;
			break;
		}

		// Turn Right
		case SDLK_RIGHT:
		case SDLK_d:
		{
			this->m_TurnLeft = false;
			this->m_TurnRight = true;
			break;
		}
	}
}

void PlayerCollectorController::OnKeyUp(const KeyUpEvent* event)
{
	switch (event->keyCode)
	{
		// Move Forawrd
		case SDLK_UP:
		case SDLK_w:
		{
			this->m_MoveForward = false;
			break;
		}

		// Turn Left
		case SDLK_LEFT:
		case SDLK_a:
		{
			this->m_TurnLeft = false;
			break;
		}

		// Turn Right
		case SDLK_RIGHT:
		case SDLK_d:
		{
			this->m_TurnRight = false;
			break;
		}
	}
}

void PlayerCollectorController::OnKeyPressed(const KeyPressedEvent* event)
{
}
