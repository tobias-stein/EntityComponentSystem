///-------------------------------------------------------------------------------------------------
/// File:	Collector.h.
///
/// Summary:	Declares the collector entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __COLLECTOR_ENTITY_H__
#define __COLLECTOR_ENTITY_H__

#include "GameObject.h"

#include "ControllerComponent.h"


class Collector : public GameObject<Collector>
{
public:

	Collector(GameObjectId spawnId, IController* controller = nullptr);
	virtual ~Collector();

}; // class Collector

#endif // __COLLECTOR_ENTITY_H__
