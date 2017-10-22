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
	m_PlayerController(controller),
	m_CollectedBounty(0.0f)
{}

Player::~Player()
{
	this->m_PlayerController.Release();
}

void Player::ResetCollectedBounty()
{
	this->m_CollectedBounty = 0.0f;
	UpdatePawnColor();
}

void Player::CollectBounty(float bounty)
{
	this->m_CollectedBounty = glm::min<float>(this->m_CollectedBounty + bounty, PLAYER_POCKET_SIZE);
	UpdatePawnColor();
}

void Player::UpdatePawnColor()
{
	GameObjectId pawnId = this->m_PlayerController.GetPossessed();
	if (pawnId == INVALID_GAMEOBJECT_ID)
		return;

	float alpha = this->m_CollectedBounty / PLAYER_POCKET_SIZE;

	ECS::ECS_Engine->GetComponentManager()->GetComponent<MaterialComponent>(pawnId)->SetColor(1.0f - alpha, 0.0f, 1.0f);
}