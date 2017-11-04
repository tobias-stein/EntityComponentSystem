///-------------------------------------------------------------------------------------------------
/// File:	CollectorAvoider.h.
///
/// Summary:	Declares the collector avoider class.
///-------------------------------------------------------------------------------------------------


#ifndef __COLLECTOR_AVOIDER_H__
#define __COLLECTOR_AVOIDER_H__

#include <ECS/ECS.h>
#include "GameEvents.h"
#include "WorldSystem.h"



class Collector;

class CollectorAvoider : public ECS::Component<CollectorAvoider>, public ECS::Event::IEventListener
{
	using DetectedCollector = std::list<const Collector*>;

private:

	void RegisterEventCallbacks();

	void OnCollisionBegin(const CollisionBeginEvent* event);
	void OnCollisionEnd(const CollisionEndEvent* event);

	DetectedCollector	m_DetectedCollector;

	float			m_ViewDistance;
	float			m_Width;

	b2PolygonShape	m_b2AvoiderShape;
	b2Fixture*		m_Avoider;

public:

	CollectorAvoider(float viewDistance, float width);
	~CollectorAvoider();

	void Initialize();
	void Destroy();


	inline const DetectedCollector& GetDetectedCollector() const { return this->m_DetectedCollector; }

	inline const float GetViewDistance() const { return this->m_ViewDistance; }

	inline const float GetWidth() const { return this->m_Width; }

	void DebugDrawAvoider();

}; // class BountyRadar

#endif // __COLLECTOR_AVOIDER_H__
