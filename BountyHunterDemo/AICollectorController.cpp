///-------------------------------------------------------------------------------------------------
/// File:	AICollectorController.cpp.
///
/// Summary:	Implements the ai collector controller class.
///-------------------------------------------------------------------------------------------------

#include "AICollectorController.h"


AICollectorController::AICollectorController(const GameObjectId collectorId, const PlayerId playerId) : AIController(collectorId)
{
	this->m_Pawn->SetPlayer(playerId);
	RegisterEventCallbacks();
	ChangeState(SPAWNED);
}

AICollectorController::~AICollectorController()
{
	UnregisterAllEventCallbacks();
}

void AICollectorController::RegisterEventCallbacks()
{
	RegisterEventCallback(&AICollectorController::OnGameObjectKilled);
	RegisterEventCallback(&AICollectorController::OnGameObjectSpawned);
}

void AICollectorController::OnGameObjectKilled(const GameObjectKilled* event)
{
	if (event->m_EntityID == this->m_Pawn->GetEntityID())
	{
		this->m_isDead = true;
	}
}

void AICollectorController::OnGameObjectSpawned(const GameObjectSpawned* event)
{
	if (event->m_EntityID == this->m_Pawn->GetEntityID())
	{
		ResetFSM();
		ChangeState(SPAWNED);
		this->m_isDead = false;
	}
}




///-------------------------------------------------------------------------------------------------
/// Update AI-Controller
///-------------------------------------------------------------------------------------------------


void AICollectorController::Update(float dt)
{
	if (this->m_isDead == false)
	{
		// Update FSM
		UpdateStateMachine();

		if (DEBUG_DRAWING_ENABLED == true)
		{
			this->DrawGizmos();
		}
	}
}


///-------------------------------------------------------------------------------------------------
/// Draw debug stuff
///-------------------------------------------------------------------------------------------------


void AICollectorController::DrawGizmos()
{
}


///-------------------------------------------------------------------------------------------------
/// State: SPAWNED 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_SPAWNED()
{
}

void AICollectorController::S_SPAWNED_ENTER()
{
}

void AICollectorController::S_SPAWNED_LEAVE()
{
}


///-------------------------------------------------------------------------------------------------
/// State: FIND_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_FIND_BOUNTY()
{
}

void AICollectorController::S_FIND_BOUNTY_ENTER()
{
}

void AICollectorController::S_FIND_BOUNTY_LEAVE()
{
}

///-------------------------------------------------------------------------------------------------
/// State: MOVE_TO_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_MOVE_TO_BOUNTY()
{
}

void AICollectorController::S_MOVE_TO_BOUNTY_ENTER()
{
}

void AICollectorController::S_MOVE_TO_BOUNTY_LEAVE()
{
}

///-------------------------------------------------------------------------------------------------
/// State: BOUNTY_COLLECTED 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_BOUNTY_COLLECTED()
{
}

void AICollectorController::S_BOUNTY_COLLECTED_ENTER()
{
}

void AICollectorController::S_BOUNTY_COLLECTED_LEAVE()
{
}


///-------------------------------------------------------------------------------------------------
/// State: STASH_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_STASH_BOUNTY()
{
}

void AICollectorController::S_STASH_BOUNTY_ENTER()
{
}

void AICollectorController::S_STASH_BOUNTY_LEAVE()
{
}
