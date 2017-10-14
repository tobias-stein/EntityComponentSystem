///-------------------------------------------------------------------------------------------------
/// File:	RegionSpawn.h.
///
/// Summary:	Declares the point spawn class.
///-------------------------------------------------------------------------------------------------

#ifndef __REGION_SPAWN_H__
#define __REGION_SPAWN_H__

#include "ISpawn.h"
#include "Bounds.h"

class RegionSpawn : public ISpawn
{
	 
private:

	Position	m_SpawnPosition;
	glm::vec3	m_SpawnDimensionHalfExpansionSize;

	glm::vec3	m_SpawnOrientation;

public:

	RegionSpawn(const Bounds& bounds, const glm::vec3& orientation);
	RegionSpawn(const Position& position, const glm::vec3& halfExpand, const glm::vec3& orientation);
	virtual ~RegionSpawn();



	// Inherited via ISpawn
	virtual SpawnInfo GetFixSpawnInfo() override;

	virtual SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z) override;

	virtual SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) override;

}; // class RegionSpawn

#endif // __REGION_SPAWN_H__
