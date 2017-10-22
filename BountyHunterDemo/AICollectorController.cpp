///-------------------------------------------------------------------------------------------------
/// File:	AICollectorController.cpp.
///
/// Summary:	Implements the ai collector controller class.
///-------------------------------------------------------------------------------------------------

#include "AICollectorController.h"

AICollectorController::AICollectorController(const GameObjectId collectorId, const PlayerId playerId) : AIController(collectorId)
{
	this->m_Pawn->SetPlayer(playerId);
}

AICollectorController::~AICollectorController()
{
}

void AICollectorController::Update(float dt)
{
}
