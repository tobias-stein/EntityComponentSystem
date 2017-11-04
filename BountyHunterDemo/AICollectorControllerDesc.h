///-------------------------------------------------------------------------------------------------
/// File:	AICollectorControllerDesc.h.
///
/// Summary:	Declares the ai collector controller description class.
///-------------------------------------------------------------------------------------------------

#ifndef __AI_COLLECTOR_CONTROLLER_DESC_H__
#define __AI_COLLECTOR_CONTROLLER_DESC_H__

#include "BountyCollectStrategy.h"

///-------------------------------------------------------------------------------------------------
/// Struct:	AICollectorControllerDesc
///
/// Summary:	Description of the ai collector controller. Holds a bunch of descriptive variables
/// that will influence actor behaviour.
///
/// Author:	Tobias Stein
///
/// Date:	4/11/2017
///-------------------------------------------------------------------------------------------------

struct AICollectorControllerDesc
{
	/// Summary:	The bounty collection strategy.
	BountyCollectStrategyType	m_BountyCollectStrategy;

	/// Summary:	This marks the propability to remain in WANDER state, else change back to FIND_BOUNTY state.
	float						m_WanderStateStayChance;

	/// Summary:	The used ratio of max allowed turn speed for steering to wander around.
	float						m_SteeringRatio_Wander;

	/// Summary:	The used ratio of max allowed turn speed for steering to avoid obstacles.
	float						m_SteeringRatio_Avoid;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	AICollectorControllerDesc()
	///
	/// Summary:	Default constructor.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	4/11/2017
	///-------------------------------------------------------------------------------------------------

	AICollectorControllerDesc() :
		m_BountyCollectStrategy(BountyCollectStrategyType::FIRST_STRATEGY),
		m_WanderStateStayChance(0.5f),
		m_SteeringRatio_Wander(0.5f),
		m_SteeringRatio_Avoid(1.0f)
	{}

}; // struct AICollectorControllerDesc

#endif // __AI_COLLECTOR_CONTROLLER_DESC_H__
