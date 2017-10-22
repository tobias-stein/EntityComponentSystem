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

	PlayerId			m_PlayerId;

public:

	Collector(GameObjectId spawnId);
	virtual ~Collector();

	virtual void OnEnable() override;
	virtual void OnDisable() override;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline void Collector::SetPlayer(const PlayerId& playerId)
	///
	/// Summary:	Sets the current player controlling this collector.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	22/10/2017
	///
	/// Parameters:
	/// playerId - 	Identifier for the player.
	///-------------------------------------------------------------------------------------------------

	inline void SetPlayer(const PlayerId playerId) { this->m_PlayerId = playerId; }

	inline const PlayerId GetPlayer() const { return this->m_PlayerId; }

	void MoveForward(float speed);
	void TurnLeft(float degrees);
	void TurnRight(float degrees);

	void Stop();
	void StopTurning();
	void StopMoving();

}; // class Collector

#endif // __COLLECTOR_ENTITY_H__
