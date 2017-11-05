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
	static RenderSystem* RS = ECS::ECS_Engine->GetSystemManager()->GetSystem<RenderSystem>();

	// draw bounty radar
	this->m_BountyRadar->DebugDrawRadar();

	// draw avoider
	this->m_CollectorAvoider->DebugDrawAvoider();


	// draw threats
	for (auto&& threat : this->m_CollectorAvoider->GetDetectedCollector())
	{
		RS->DrawLine(this->m_Pawn->GetComponent<TransformComponent>()->GetPosition(), threat->GetComponent<TransformComponent>()->GetPosition(), false, true, Color3f(1.0f, 0.0f, 0.0f));
	}

	switch (this->GetActiveState())
	{
		case MOVE_TO_BOUNTY:
		{
			// draw selected bounty
			if (this->m_TargetedBounty != nullptr)
			{
				RS->DrawLine(this->m_Pawn->GetComponent<TransformComponent>()->GetPosition(), this->m_TargetedBountyPosition, false, true, Color3f(0.0f, 1.0f, 0.0f));
			}
			break;
		}

		case STASH_BOUNTY:
		{
			// draw selected bounty
			RS->DrawLine(this->m_Pawn->GetComponent<TransformComponent>()->GetPosition(), this->m_MyStashPosition, false, true, Color3f(0.0f, 1.0f, 0.0f));
			break;
		}
	}
}

bool AICollectorController::AvoidObstacles()
{
	auto threats = this->m_CollectorAvoider->GetDetectedCollector();

	
	return false;
}

float AICollectorController::MoveToTarget(const Position2D & target)
{

	// Get Collector and bounty transform
	auto collectorTF = this->m_Pawn->GetComponent<TransformComponent>();

	if (AvoidObstacles() == true)
		return glm::distance2(target, Position2D(collectorTF->GetPosition()));

	glm::vec2 F = glm::normalize(collectorTF->GetRight());
	glm::vec2 T = glm::normalize(target - Position2D(collectorTF->GetPosition()));
	float dot = glm::dot(F, T);

	float steering = this->m_AICD.m_SteeringRatio_Target * COLLECTOR_MAX_TURN_SPEED;
	float speedRatio = 0.0f;
	if (glm::sign(dot) < 0.0f)
	{
		this->m_Pawn->TurnLeft(glm::abs(dot) * steering);
		speedRatio = 1.0f + dot;
	}
	else
	{
		this->m_Pawn->TurnRight(glm::abs(dot) * steering);
		speedRatio = 1.0f - dot;
	}

	this->m_Pawn->MoveForward(speedRatio * COLLECTOR_MAX_MOVE_SPEED);

	return glm::distance2(target, Position2D(collectorTF->GetPosition()));
}


///-------------------------------------------------------------------------------------------------
/// State: SPAWNED 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_SPAWNED()
{
	this->m_TargetedBounty = nullptr;
	this->m_Pawn->Stop();
	ChangeState(FIND_BOUNTY);
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
	assert(this->m_TargetedBounty == nullptr && "AI controller is in invalid state!");

	// Use bounty collect strategy to get next bounty to collect ...
	Bounty* nextTarget = (Bounty*)BountyCollectStrategies[this->m_AICD.m_BountyCollectStrategy](this->m_Pawn, this->m_BountyRadar->GetDetectedBounty());
	if (nextTarget == nullptr)
	{
		ChangeState(WANDER);
	}
	else
	{
		this->m_TargetedBounty = nextTarget;
		this->m_TargetedBountyPosition = nextTarget->GetComponent<TransformComponent>()->GetPosition();
		ChangeState(MOVE_TO_BOUNTY);
	}
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
/// State: WANDER 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_WANDER()
{
	// roll the dice, if random value exceeds a given chance: chnage back to FIND_BOUNTY state
	if (glm::linearRand(0.0f, 1.0f) > this->m_AICD.m_WanderStateStayChance)
	{
		ChangeState(FIND_BOUNTY);
		return;
	}
	// else let ai-controller randomly wander the collector across the world ...

	// Avoid obstacles
	if (AvoidObstacles() == true)
		return;

	// move full speed ahead
	this->m_Pawn->MoveForward(COLLECTOR_MAX_MOVE_SPEED);

	return;

	float steering = this->m_AICD.m_SteeringRatio_Wander * COLLECTOR_MAX_TURN_SPEED;

	// steer to the left
	if (glm::linearRand(0.0f, 1.0f) > 0.5f)
	{
		this->m_Pawn->TurnLeft(steering);
	}
	// steer to the right
	else
	{
		this->m_Pawn->TurnRight(steering);
	}
}

void AICollectorController::S_WANDER_ENTER()
{
	SDL_Log("Player #%d - entered 'WANDER' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_WANDER_LEAVE()
{
	SDL_Log("Player #%d - left 'WANDER' state.", this->m_Pawn->GetPlayer());
}

///-------------------------------------------------------------------------------------------------
/// State: MOVE_TO_BOUNTY 
///-------------------------------------------------------------------------------------------------

void AICollectorController::S_MOVE_TO_BOUNTY()
{
	// check if bounty was collected
	if (this->m_TargetedBounty->IsActive() == false)
	{
		ChangeState(BOUNTY_COLLECTED);
		return;
	}
	// else move to bounty ...
	
	this->MoveToTarget(this->m_TargetedBountyPosition);
}

void AICollectorController::S_MOVE_TO_BOUNTY_ENTER()
{
	this->m_Pawn->Stop();
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
	// how full the player pocket is, in percentage [0.0 - 1.0]
	float collectorPocketFillState = this->m_Pawn->GetCollectedBounty() / PLAYER_POCKET_SIZE;

	if (collectorPocketFillState >= this->m_AICD.m_StashBountyThreshold)
	{
		ChangeState(STASH_BOUNTY);
	}
	// pockets still not full yet ..
	else
	{
		ChangeState(FIND_BOUNTY);
	}
}

void AICollectorController::S_BOUNTY_COLLECTED_ENTER()
{
	this->m_TargetedBounty = nullptr;
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
	if (this->MoveToTarget(this->m_MyStashPosition) <= 0.25f)
		ChangeState(FIND_BOUNTY);
}

void AICollectorController::S_STASH_BOUNTY_ENTER()
{
	SDL_Log("Player #%d - entered 'STASH_BOUNTY' state.", this->m_Pawn->GetPlayer());
}

void AICollectorController::S_STASH_BOUNTY_LEAVE()
{
	SDL_Log("Player #%d - left 'STASH_BOUNTY' state.", this->m_Pawn->GetPlayer());
}
