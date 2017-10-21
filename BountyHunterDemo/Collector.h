///-------------------------------------------------------------------------------------------------
/// File:	Collector.h.
///
/// Summary:	Declares the collector entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __COLLECTOR_ENTITY_H__
#define __COLLECTOR_ENTITY_H__

#include "GameObject.h"

#include "RigidbodyComponent.h"

class Collector : public GameObject<Collector>, public ECS::Event::IEventListener
{
private:

	TransformComponent*	m_ThisTransform;
	RigidbodyComponent* m_ThisRigidbody;

public:

	Collector(GameObjectId spawnId);
	virtual ~Collector();

	virtual void OnEnable() override;
	virtual void OnDisable() override;

	void MoveForward(float speed);
	void TurnLeft(float degrees);
	void TurnRight(float degrees);

	void Stop();
	void StopTurning();
	void StopMoving();

}; // class Collector

#endif // __COLLECTOR_ENTITY_H__
