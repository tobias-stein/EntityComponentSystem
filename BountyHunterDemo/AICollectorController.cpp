///-------------------------------------------------------------------------------------------------
/// File:	AICollectorController.cpp.
///
/// Summary:	Implements the ai collector controller class.
///-------------------------------------------------------------------------------------------------

#include "AICollectorController.h"

#include "PlayerSystem.h"
#include "RenderSystem.h" // debug draw

AICollectorController::AICollectorController(const GameObjectId collectorId, const PlayerId playerId, const AICollectorControllerDesc& desc) : 
	AIController(collectorId),
	m_AICD(desc),
	m_MyStash(nullptr),
	m_TargetedBounty(nullptr),
	m_isDead(false)
{
	RegisterEventCallbacks();


	// get collector's stash and stash position
	Player* player = ECS::ECS_Engine->GetSystemManager()->GetSystem<PlayerSystem>()->GetPlayer(playerId);
	this->m_MyStash = (Stash*)ECS::ECS_Engine->GetEntityManager()->GetEntity(player->GetStash());
	this->m_MyStashPosition = this->m_MyStash->GetComponent<TransformComponent>()->GetPosition();


	// add BountyRadar to collector entity
	this->m_BountyRadar = ECS::ECS_Engine->GetComponentManager()->AddComponent<BountyRadar>(collectorId, AI_VIEW_DISTANCE_BOUNTY, AI_BOUNTY_RADAR_LOS);
	this->m_BountyRadar->Initialize();

	// add CollectorAvoider to collector entity
	this->m_CollectorAvoider = ECS::ECS_Engine->GetComponentManager()->AddComponent<CollectorAvoider>(collectorId, AI_VIEW_DISTANCE_OBSTACLE, ECS::ECS_Engine->GetComponentManager()->GetComponent<TransformComponent>(collectorId)->GetScale().x);
	this->m_CollectorAvoider->Initialize();

	this->m_Pawn->SetPlayer(playerId);
	ChangeState(SPAWNED);
}

AICollectorController::~AICollectorController()
{
	UnregisterAllEventCallbacks();

	// remove BountyRadar component from collector entity
	//ECS::ECS_Engine->GetComponentManager()->RemoveComponent<BountyRadar>(this->GetPossessed());
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
	// draw bounty radar
	this->m_BountyRadar->DebugDrawRadar();

	// draw avoider
	this->m_CollectorAvoider->DebugDrawAvoider();
}


///-------------------------------------------------------------------------------------------------
/// State: SPAWNED 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_SPAWNED()
{
}

void AICollectorController::S_SPAWNED_ENTER()
{
	SDL_Log("Player #%d - entered 'SPAWNED' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_SPAWNED_LEAVE()
{
	SDL_Log("Player #%d - left 'SPAWNED' state.", this->m_Pawn->GetPlayer());
}


///-------------------------------------------------------------------------------------------------
/// State: FIND_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_FIND_BOUNTY()
{
}

void AICollectorController::S_FIND_BOUNTY_ENTER()
{
	SDL_Log("Player #%d - entered 'FIND_BOUNTY' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_FIND_BOUNTY_LEAVE()
{
	SDL_Log("Player #%d - left 'FIND_BOUNTY' state.", this->m_Pawn->GetPlayer());
}

///-------------------------------------------------------------------------------------------------
/// State: MOVE_TO_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_MOVE_TO_BOUNTY()
{
}

void AICollectorController::S_MOVE_TO_BOUNTY_ENTER()
{
	SDL_Log("Player #%d - entered 'MOVE_TO_BOUNTY' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_MOVE_TO_BOUNTY_LEAVE()
{
	SDL_Log("Player #%d - left 'MOVE_TO_BOUNTY' state.", this->m_Pawn->GetPlayer());
}

///-------------------------------------------------------------------------------------------------
/// State: BOUNTY_COLLECTED 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_BOUNTY_COLLECTED()
{
}

void AICollectorController::S_BOUNTY_COLLECTED_ENTER()
{
	SDL_Log("Player #%d - entered 'BOUNTY_COLLECTED' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_BOUNTY_COLLECTED_LEAVE()
{
	SDL_Log("Player #%d - left 'BOUNTY_COLLECTED' state.", this->m_Pawn->GetPlayer());
}


///-------------------------------------------------------------------------------------------------
/// State: STASH_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_STASH_BOUNTY()
{
}

void AICollectorController::S_STASH_BOUNTY_ENTER()
{
	SDL_Log("Player #%d - entered 'STASH_BOUNTY' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_STASH_BOUNTY_LEAVE()
{
	SDL_Log("Player #%d - left 'STASH_BOUNTY' state.", this->m_Pawn->GetPlayer());
}
