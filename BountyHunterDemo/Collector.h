///-------------------------------------------------------------------------------------------------
/// File:	Collector.h.
///
/// Summary:	Declares the collector entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __COLLECTOR_ENTITY_H__
#define __COLLECTOR_ENTITY_H__

#include "GameObject.h"


class Collector : public GameObject<Collector>
{
private:

	TransformComponent*	m_ThisTransform;

public:

	Collector(GameObjectId spawnId);
	virtual ~Collector();

	void MoveForward(float speed);
	void TurnLeft(float degrees);
	void TurnRight(float degrees);

}; // class Collector

#endif // __COLLECTOR_ENTITY_H__
