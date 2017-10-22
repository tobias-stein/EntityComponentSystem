///-------------------------------------------------------------------------------------------------
/// File:	AICollectorController.h.
///
/// Summary:	Declares the ai collector controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __AI_COLLECTOR_CONTROLLER_H__
#define __AI_COLLECTOR_CONTROLLER_H__

#include "AIController.h"
#include "Collector.h"

class AICollectorController : public AIController<Collector>
{
public:

	AICollectorController(const GameObjectId collectorId, const PlayerId playerId);
	virtual ~AICollectorController();


	// Inherited via AIController
	virtual void Update(float dt) override;

}; // class AICollectorController

#endif // __AI_COLLECTOR_CONTROLLER_H__
