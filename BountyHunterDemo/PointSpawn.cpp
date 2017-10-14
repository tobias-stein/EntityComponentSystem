///-------------------------------------------------------------------------------------------------
/// File:	PointSpawn.cpp.
///
/// Summary:	Implements the point spawn class.
///-------------------------------------------------------------------------------------------------

#include "PointSpawn.h"

PointSpawn::PointSpawn(const Position& position, const glm::vec3& orientation) :
	m_SpawnPosition(position),
	m_SpawnOrientation(orientation)
{}

PointSpawn::~PointSpawn()
{}

SpawnInfo PointSpawn::GetFixSpawnInfo()
{
	return SpawnInfo(m_SpawnPosition, m_SpawnOrientation);
}

SpawnInfo PointSpawn::GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z)
{
	return SpawnInfo(m_SpawnPosition, m_SpawnOrientation);
}

SpawnInfo PointSpawn::SampleRandomSpawnInfo(RandomSpawnSampler sample)
{
	return SpawnInfo(m_SpawnPosition, m_SpawnOrientation);
}
