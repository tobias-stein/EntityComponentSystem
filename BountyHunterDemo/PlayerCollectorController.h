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
public:

	PlayerCollectorController(const GameObjectId gameObjectId);
	virtual ~PlayerCollectorController();

	// Inherited via PlayerController
	virtual void Update(float dt) override;
	virtual void OnKeyDown(const KeyDownEvent * event) override;
	virtual void OnKeyUp(const KeyUpEvent * event) override;
	virtual void OnKeyPressed(const KeyPressedEvent * event) override;

}; // class PlayerCollectorController

#endif // __PLAYER_COLLECTOR_CONTROLLER_H__
