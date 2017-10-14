///-------------------------------------------------------------------------------------------------
/// File:	PointSpawn.h.
///
/// Summary:	Declares the point spawn class.
///-------------------------------------------------------------------------------------------------

#ifndef __POINT_SPAWN_H__
#define __POINT_SPAWN_H__

#include "ISpawn.h"

class PointSpawn : public ISpawn
{
private:

	Position	m_SpawnPosition;
	glm::vec3	m_SpawnOrientation;

public:

	PointSpawn(const Position& position, const glm::vec3& orientation = glm::vec3(0.0f));
	virtual ~PointSpawn();

	// Inherited via ISpawn
	virtual SpawnInfo GetFixSpawnInfo() override;
	virtual SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z) override;
	virtual SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) override;

}; // class PointSpawn

#endif // __POINT_SPAWN_H__
