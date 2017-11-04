///-------------------------------------------------------------------------------------------------
/// File:	AICollectorController.h.
///
/// Summary:	Declares the ai collector controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __AI_COLLECTOR_CONTROLLER_H__
#define __AI_COLLECTOR_CONTROLLER_H__

#include "AIController.h"
#include "Collector.h"
#include "Stash.h"
#include "Bounty.h"

#include "AICollectorControllerDesc.h"

#include "SimpleFSM.h"

#include "BountyRadar.h"
#include "CollectorAvoider.h"

class AICollectorController : public AIController<Collector>, public SimpleFSM
{

	enum AICollectorControllerStates
	{
		SPAWNED = 0,
		FIND_BOUNTY,
		WANDER,
		MOVE_TO_BOUNTY,
		BOUNTY_COLLECTED,
		STASH_BOUNTY
	}; // enum AICollectorControllerStates

	///-------------------------------------------------------------------------------------------------
	/// Summary:	AI Collector Controller State Transitions.
	///
	///				  +-------------+
	///				  |   SPAWNED   |        +--------+
	///				  +-------------+    +-->| WANDER |
	///				         |           |   +--------+
	///				         v           |     |
	///				   +-------------+---+     |
	///			  +--->| FIND_BOUNTY |         |
	///			  |    +-------------+<--------+
	///			  |          |                 |
	///			  |          v                 |
	///			  |     +----------------+     |
	///			  |     | MOVE_TO_BOUNTY |     |
	///			  |     +----------------+     |
	///			  |          |                 |
	///			  |          |                 |
	///			  |          |                 |
	///			  |          |                 |
	///			  |          v                 |
	///			  |     +------------------+   | 
	///			  |     | BOUNTY_COLLECTED |---+ 
	///			  |     +------------------+               
	///			  |          |                    
	///			  |          v                    
	///			  |    +--------------+           
	///			  +----| STASH_BOUNTY |
	///			       +--------------+               
	///-------------------------------------------------------------------------------------------------


	// Define FSM Transition table
	BEGIN_TRANSITION_TABLE

		// Initial State
		TRANSITION_ENTRY(NULL_STATE									, AICollectorController::S_SPAWNED			, AICollectorController::S_SPAWNED_ENTER			, NO_ONLEAVE_PROC									, SPAWNED)

		// Transitions to 'FIND_BOUNTY'
		TRANSITION_ENTRY(AICollectorController::S_SPAWNED			, AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_FIND_BOUNTY_ENTER		, AICollectorController::S_SPAWNED_LEAVE			, FIND_BOUNTY)
		TRANSITION_ENTRY(AICollectorController::S_WANDER			, AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_FIND_BOUNTY_ENTER		, AICollectorController::S_WANDER_LEAVE				, FIND_BOUNTY)
		TRANSITION_ENTRY(AICollectorController::S_BOUNTY_COLLECTED	, AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_FIND_BOUNTY_ENTER		, AICollectorController::S_BOUNTY_COLLECTED_LEAVE	, FIND_BOUNTY)
		TRANSITION_ENTRY(AICollectorController::S_STASH_BOUNTY		, AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_FIND_BOUNTY_ENTER		, AICollectorController::S_STASH_BOUNTY_LEAVE		, FIND_BOUNTY)

		// Transitions to 'WANDER'
		TRANSITION_ENTRY(AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_WANDER			, AICollectorController::S_WANDER_ENTER				, AICollectorController::S_FIND_BOUNTY_LEAVE		, WANDER)

		// Transitions to 'MOVE_TO_BOUNTY'
		TRANSITION_ENTRY(AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_MOVE_TO_BOUNTY	, AICollectorController::S_MOVE_TO_BOUNTY_ENTER		, AICollectorController::S_FIND_BOUNTY_LEAVE		, MOVE_TO_BOUNTY)

		// Transitions to 'BOUNTY_COLLECTED'
		TRANSITION_ENTRY(AICollectorController::S_MOVE_TO_BOUNTY	, AICollectorController::S_BOUNTY_COLLECTED	, AICollectorController::S_BOUNTY_COLLECTED_ENTER	, AICollectorController::S_MOVE_TO_BOUNTY_LEAVE		, BOUNTY_COLLECTED)

		// Transitions to 'STASH_BOUNTY'
		TRANSITION_ENTRY(AICollectorController::S_BOUNTY_COLLECTED	, AICollectorController::S_STASH_BOUNTY		, AICollectorController::S_STASH_BOUNTY_ENTER		, AICollectorController::S_BOUNTY_COLLECTED_LEAVE	, BOUNTY_COLLECTED)

	END_TRANSITION_TABLE


	// FSM State callback functions
	
	// 'SPAWNED' state
	void S_SPAWNED();
	void S_SPAWNED_ENTER();
	void S_SPAWNED_LEAVE();
	
	// 'FIND_BOUNTY' state
	void S_FIND_BOUNTY();
	void S_FIND_BOUNTY_ENTER();
	void S_FIND_BOUNTY_LEAVE();
	
	// 'WANDER' state
	void S_WANDER();
	void S_WANDER_ENTER();
	void S_WANDER_LEAVE();

	// 'MOVE_TO_BOUNTY' state
	void S_MOVE_TO_BOUNTY();
	void S_MOVE_TO_BOUNTY_ENTER();
	void S_MOVE_TO_BOUNTY_LEAVE();
	
	// 'BOUNTY_COLLECTED' state
	void S_BOUNTY_COLLECTED();
	void S_BOUNTY_COLLECTED_ENTER();
	void S_BOUNTY_COLLECTED_LEAVE();
	
	// 'STASH_BOUNTY' state
	void S_STASH_BOUNTY();
	void S_STASH_BOUNTY_ENTER();
	void S_STASH_BOUNTY_LEAVE();


	void RegisterEventCallbacks();

	void OnGameObjectKilled(const GameObjectKilled* event);
	void OnGameObjectSpawned(const GameObjectSpawned* event);

	void DrawGizmos();


	AICollectorControllerDesc	m_AICD;

	BountyRadar*				m_BountyRadar;

	CollectorAvoider*			m_CollectorAvoider;

	
	bool						m_isDead;

	// Collector's stash and stash world position
	Stash*						m_MyStash;
	Position2D					m_MyStashPosition;

	// Current targeted bounty
	Bounty*						m_TargetedBounty;
	Position2D					m_TargetedBountyPosition;

public:

	AICollectorController(const GameObjectId collectorId, const PlayerId playerId, const AICollectorControllerDesc& desc);
	virtual ~AICollectorController();

	// Inherited via AIController
	virtual void Update(float dt) override;

}; // class AICollectorController

#endif // __AI_COLLECTOR_CONTROLLER_H__
