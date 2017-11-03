///-------------------------------------------------------------------------------------------------
/// File:	BountyRadar.h.
///
/// Summary:	Declares the bounty radar class.
///-------------------------------------------------------------------------------------------------

#ifndef __BOUNTY_RADAR_H__
#define __BOUNTY_RADAR_H__

#include <ECS/ECS.h>
#include "GameEvents.h"

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

public:

	BountyRadar(float viewDistance, float lineOfSight);
	~BountyRadar();

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


}; // class BountyRadar

#endif // __BOUNTY_RADAR_H__
