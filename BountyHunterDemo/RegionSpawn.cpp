///-------------------------------------------------------------------------------------------------
/// File:	RegionSpawn.cpp.
///
/// Summary:	Implements the region spawn class.
///-------------------------------------------------------------------------------------------------

#include "RegionSpawn.h"

RegionSpawn::RegionSpawn(const Bounds& bounds, const glm::vec3& orientation) :
	m_SpawnOrientation(orientation)
{
	this->m_SpawnPosition					= bounds.minBound + (bounds.maxBound - bounds.minBound) * 0.5f;
	this->m_SpawnDimensionHalfExpansionSize = (bounds.maxBound - bounds.minBound) * 0.5f;
}

RegionSpawn::RegionSpawn(const Position& position, const glm::vec3& halfExpand, const glm::vec3& orientation) :
	m_SpawnOrientation(orientation),
	m_SpawnPosition(position),
	m_SpawnDimensionHalfExpansionSize(halfExpand)
{}

RegionSpawn::~RegionSpawn()
{}

SpawnInfo RegionSpawn::GetFixSpawnInfo()
{
	return SpawnInfo(this->m_SpawnPosition, this->m_SpawnOrientation);
}

SpawnInfo RegionSpawn::GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z)
{
	const Position position = (this->m_SpawnPosition - this->m_SpawnDimensionHalfExpansionSize) + (glm::vec3(uniform_x, uniform_y, uniform_z) * (2.0f * this->m_SpawnDimensionHalfExpansionSize));

	return SpawnInfo(position, this->m_SpawnOrientation);
}

SpawnInfo RegionSpawn::SampleRandomSpawnInfo(RandomSpawnSampler sample)
{
	Position position(0.0f);
	
	switch (sample)
	{
		case Unitform: position = this->m_SpawnPosition + (glm::linearRand(glm::vec3(-1.0f), glm::vec3(1.0f)) * this->m_SpawnDimensionHalfExpansionSize); 
			break;

		case Spherical: position = this->m_SpawnPosition + (glm::sphericalRand(1.0f) * this->m_SpawnDimensionHalfExpansionSize); 
			break;

		case Gaussian: position = this->m_SpawnPosition + (glm::gaussRand(glm::vec3(0.0f), glm::vec3(1.0f)) * this->m_SpawnDimensionHalfExpansionSize); 
			break;
	}

	return SpawnInfo(position, this->m_SpawnOrientation);
}
