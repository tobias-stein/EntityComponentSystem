///-------------------------------------------------------------------------------------------------
/// File:	PlayerCollectorController.h.
///
/// Summary:	Declares the player collector controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __PLAYER_COLLECTOR_CONTROLLER_H__
#define __PLAYER_COLLECTOR_CONTROLLER_H__

#include "PlayerController.h"
#include "Collector.h"
class PlayerCollectorController : public PlayerController<Collector>
{
private:

	uint8_t m_MoveForward	: 1;
	uint8_t m_TurnLeft		: 1;
	uint8_t m_TurnRight		: 1;
	uint8_t __padding		: 5;

public:

	PlayerCollectorController(const GameObjectId collectorId, const PlayerId playerId);
	virtual ~PlayerCollectorController();

	// Inherited via PlayerController
	virtual void Update(float dt) override;
	virtual void OnKeyDown(const KeyDownEvent * event) override;
	virtual void OnKeyUp(const KeyUpEvent * event) override;
	virtual void OnKeyPressed(const KeyPressedEvent * event) override;

}; // class PlayerCollectorController

#endif // __PLAYER_COLLECTOR_CONTROLLER_H__
