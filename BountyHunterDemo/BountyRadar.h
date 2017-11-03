///-------------------------------------------------------------------------------------------------
/// File:	BountyRadar.h.
///
/// Summary:	Declares the bounty radar class.
///-------------------------------------------------------------------------------------------------

#ifndef __BOUNTY_RADAR_H__
#define __BOUNTY_RADAR_H__

#include <ECS/ECS.h>
#include "GameEvents.h"
#include "WorldSystem.h"



class Collector;
class Bounty;

class BountyRadar : public ECS::Component<BountyRadar>, public ECS::Event::IEventListener
{
	using DetectedBounty = std::list<const Bounty*>;

private:

	void RegisterEventCallbacks();

	void OnCollisionBegin(const CollisionBeginEvent* event);
	void OnCollisionEnd(const CollisionEndEvent* event);


	void RadarAddBountyAction(Collector* collector, Bounty* bounty);
	void RadarRemoveBountyAction(Collector* collector, Bounty* bounty);

	DetectedBounty	m_DetectedBounty;

	float			m_ViewDistance;
	float			m_LOS;

	b2PolygonShape	m_b2RadarShape;
	b2Fixture*		m_Radar;

public:	

	BountyRadar(float viewDistance, float lineOfSight);
	~BountyRadar();

	void Initialize();
	void Destroy();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline const DetectedBounty& BountyRadar::GetDetectedBounty() const
	///
	/// Summary:	Gets detected bounty.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	1/11/2017
	///
	/// Returns:	The detected bounty.
	///-------------------------------------------------------------------------------------------------

	inline const DetectedBounty& GetDetectedBounty() const { return this->m_DetectedBounty; }

	inline const float GetViewDistance() const { return this->m_ViewDistance; }

	inline const float GetLineOfSight() const { return this->m_LOS; }

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void BountyRadar::DebugDrawRadar();
	///
	/// Summary:	Draws the radar's outline.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	3/11/2017
	///-------------------------------------------------------------------------------------------------

	void DebugDrawRadar();

}; // class BountyRadar

#endif // __BOUNTY_RADAR_H__
