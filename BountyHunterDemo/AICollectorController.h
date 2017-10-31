///-------------------------------------------------------------------------------------------------
/// File:	AICollectorController.h.
///
/// Summary:	Declares the ai collector controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __AI_COLLECTOR_CONTROLLER_H__
#define __AI_COLLECTOR_CONTROLLER_H__

#include "AIController.h"
#include "Collector.h"

#include "SimpleFSM.h"

class AICollectorController : public AIController<Collector>, public SimpleFSM
{

	enum AICollectorControllerStates
	{
		SPAWNED = 0,
		FIND_BOUNTY,
		MOVE_TO_BOUNTY,
		BOUNTY_COLLECTED,
		STASH_BOUNTY
	}; // enum AICollectorControllerStates

	///-------------------------------------------------------------------------------------------------
	/// Summary:	AI Collector Controller State Transitions.
	///
	///				  +-------------+
	///				  |   SPAWNED   |
	///				  +-------------+
	///				         |
	///				         v
	///				   +-------------+
	///			  +--->| FIND_BOUNTY |<--------+
	///			  |    +-------------+         |
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
		TRANSITION_ENTRY(AICollectorController::S_BOUNTY_COLLECTED	, AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_FIND_BOUNTY_ENTER		, AICollectorController::S_BOUNTY_COLLECTED_LEAVE	, FIND_BOUNTY)
		TRANSITION_ENTRY(AICollectorController::S_STASH_BOUNTY		, AICollectorController::S_FIND_BOUNTY		, AICollectorController::S_FIND_BOUNTY_ENTER		, AICollectorController::S_STASH_BOUNTY_LEAVE		, FIND_BOUNTY)

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
	
	// 'FIND_BOUNTY' gamestate
	void S_FIND_BOUNTY();
	void S_FIND_BOUNTY_ENTER();
	void S_FIND_BOUNTY_LEAVE();
	
	// 'MOVE_TO_BOUNTY' gamestate
	void S_MOVE_TO_BOUNTY();
	void S_MOVE_TO_BOUNTY_ENTER();
	void S_MOVE_TO_BOUNTY_LEAVE();
	
	// 'BOUNTY_COLLECTED' gamestate
	void S_BOUNTY_COLLECTED();
	void S_BOUNTY_COLLECTED_ENTER();
	void S_BOUNTY_COLLECTED_LEAVE();
	
	// 'STASH_BOUNTY' gamestate
	void S_STASH_BOUNTY();
	void S_STASH_BOUNTY_ENTER();
	void S_STASH_BOUNTY_LEAVE();


	void RegisterEventCallbacks();

	void OnGameObjectKilled(const GameObjectKilled* event);
	void OnGameObjectSpawned(const GameObjectSpawned* event);

	void DrawGizmos();



	bool m_isDead;

public:

	AICollectorController(const GameObjectId collectorId, const PlayerId playerId);
	virtual ~AICollectorController();


	// Inherited via AIController
	virtual void Update(float dt) override;

}; // class AICollectorController

#endif // __AI_COLLECTOR_CONTROLLER_H__
