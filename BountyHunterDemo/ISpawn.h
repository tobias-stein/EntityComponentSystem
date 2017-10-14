///-------------------------------------------------------------------------------------------------
/// File:	ISpawn.h.
///
/// Summary:	Declares the ISpawn interface.
///-------------------------------------------------------------------------------------------------

#ifndef __I_SPAWN_H__
#define __I_SPAWN_H__

#include "math.h"

struct SpawnInfo
{
	Position	m_SpawnPosition;
	glm::vec3	m_SpawnOrientation;

	SpawnInfo() :
		m_SpawnPosition(Position(0.0f)),
		m_SpawnOrientation(glm::vec3(0.0f))
	{}

	SpawnInfo(const Position& position, const glm::vec3& orientation) :
		m_SpawnPosition(position),
		m_SpawnOrientation(orientation)
	{}
};

enum RandomSpawnSampler
{
	Unitform = 0,
	Spherical,
	Gaussian,
};

class ISpawn
{
public:

	

	ISpawn()
	{}

	virtual ~ISpawn()
	{}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual SpawnInfo ISpawn::GetFixSpawnInfo() = 0;
	///
	/// Summary:	Returns a fixed spawn location that won't change.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	14/10/2017
	///
	/// Returns:	The fix spawn information.
	///-------------------------------------------------------------------------------------------------

	virtual SpawnInfo GetFixSpawnInfo() = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual SpawnInfo ISpawn::GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z) = 0;
	///
	/// Summary:	Returns a spawn location relatively offestet from the left-top spawn point that can be
	/// returned by this Spawn.
	/// 
	/// Example:
	/// 
	/// left-top-most spawn location
	///            |
	///            v
	/// (0.0, 0.0) x--------------+
	///            |              |
	///            |              | 
	///            |              |
	///            |              |
	///            +--------------+ (1.0, 1.0)
	///                           ^
	///                           |
	///                 right-bottom-most spawn location
	/// Author:	Tobias Stein
	///
	/// Date:	14/10/2017
	///
	/// Parameters:
	/// uniform_x - 	The uniform x coordinate.
	/// uniform_y - 	The uniform y coordinate.
	/// uniform_z - 	The uniform z coordinate.
	/// 
	/// Returns:	The relative spawn information.
	///-------------------------------------------------------------------------------------------------

	virtual SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z) = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// virtual SpawnInfo ISpawn::SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) = 0;
	///
	/// Summary:	Samples random spawn information from this spawn. The extra parameter can be used to controll
	/// the sampling, by default its set to uniform sampling.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	14/10/2017
	///
	/// Parameters:
	/// sample - 	(Optional) The sample.
	///
	/// Returns:	A SpawnInfo.
	///-------------------------------------------------------------------------------------------------

	virtual SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) = 0;

}; // class ISpawn

#endif // __I_SPAWN_H__
