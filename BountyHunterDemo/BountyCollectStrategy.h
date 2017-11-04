///-------------------------------------------------------------------------------------------------
/// File:	BountyCollection.h.
///
/// Summary:	Declares the bounty collection strategy class.
///-------------------------------------------------------------------------------------------------

#ifndef __BOUNTY_COLLECT_STRATEGY_H__
#define __BOUNTY_COLLECT_STRATEGY_H__

#include "Collector.h"
#include "Bounty.h"

enum BountyCollectStrategyType
{
	NULL_STRATEGY = 0,
	FIRST_STRATEGY,
	CLOSEST_DISTANCE_STRATEGY,
	HIGHEST_VALUE_STRATEGY,
	DISTANCE_VS_VALUE_STRATEGY,

	MAX_COLLECT_STRATEGIES
}; // enum BountyCollectStrategy



/// Summary:	The bounty collect strategy. Returns a bounty from the given list of bounties
/// w.r.t. a certain strategy. If no bounty can be determined a nulpltr is returned.
using BountyCollectStrategy = std::function<const Bounty* (Collector*, const std::list<const Bounty*>&)>;

static const BountyCollectStrategy BountyCollectStrategies[BountyCollectStrategyType::MAX_COLLECT_STRATEGIES]
{
	/// Summary:	Always returns nullptr.
	[](Collector* collector, const std::list<const Bounty*>& bountyList) -> const Bounty*
	{
		return nullptr;
	},

	/// Summary:	Always returns the first bounty of the provided list.
	[](Collector* collector, const std::list<const Bounty*>& bountyList) -> const Bounty*
	{
		return bountyList.empty() == true ? nullptr : bountyList.front();
	},

	/// Summary:	Returns the geograpcially closest bounty.
	[](Collector* collector, const std::list<const Bounty*>& bountyList) -> const Bounty*
	{
		if (bountyList.empty() == true)
			return nullptr;

		Position2D collectorPosition = collector->GetComponent<TransformComponent>()->GetPosition();

		auto it = bountyList.begin();
		Bounty* closestBounty = (Bounty*)(*it);
		float D = glm::distance2(collectorPosition, Position2D(closestBounty->GetComponent<TransformComponent>()->GetPosition()));
		
		++it;
		for (it; it != bountyList.end(); ++it)
		{
			Bounty* bounty = (Bounty*)(*it);

			float d = glm::distance2(collectorPosition, Position2D(bounty->GetComponent<TransformComponent>()->GetPosition()));
			if (d < D)
			{
				D = d;
				closestBounty = bounty;
			}
		}

		return closestBounty;
	},

	/// Summary:	Returns the bounty with the highest value.
	[](Collector* collector, const std::list<const Bounty*>& bountyList) -> const Bounty*
	{
		if (bountyList.empty() == true)
			return nullptr;

		auto it = bountyList.begin();
		Bounty* highestBounty = (Bounty*)(*it);
		float V = highestBounty->GetBounty();

		++it;
		for (it; it != bountyList.end(); ++it)
		{
			float v = (*it)->GetBounty();
			if (v < V)
			{
				V = v;
				highestBounty = (Bounty*)(*it);
			}
		}

		return highestBounty;
	},

	/// Summary:	Distance vs. Value strategy. Returns the bounty with the highest value and lowest distance.
	[](Collector* collector, const std::list<const Bounty*>& bountyList) -> const Bounty*
	{
		if (bountyList.empty() == true)
			return nullptr;		

		assert(false && "Not implemented yet");
		return nullptr;
	}
};

#endif // __BOUNTY_COLLECT_STRATEGY_H__
