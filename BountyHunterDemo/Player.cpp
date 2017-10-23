///-------------------------------------------------------------------------------------------------
/// File:	Player.cpp.
///
/// Summary:	Implements the player class.
///-------------------------------------------------------------------------------------------------

#include "Player.h"

#include "MaterialComponent.h"

Player::Player(const PlayerId playerId, const char* playerName, const Controller& controller) :
	m_PlayerID(playerId),
	m_PlayerName(playerName),
	m_PlayerController(controller)
{}

Player::~Player()
{
	this->m_PlayerController.Release();
}

