///-------------------------------------------------------------------------------------------------
/// File:	Spawn.h.
///
/// Summary:	Declares the spawn class.
///-------------------------------------------------------------------------------------------------


#ifndef __SPAWN_H__
#define __SPAWN_H__

// spawns
#include "PointSpawn.h"
#include "RegionSpawn.h"

class Spawn
{
private:

	ISpawn* m_SpawnImpl;

protected:

	inline void DeleteSpawn()
	{
		delete this->m_SpawnImpl;
		this->m_SpawnImpl = nullptr;
	}

public:

	///-------------------------------------------------------------------------------------------------
	/// Fn:	Spawn::Spawn(ISpawn* spawnImpl)
	///
	/// Summary:	Constructor. Spawn will take owenership of provided spawn object.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	14/10/2017
	///
	/// Parameters:
	/// spawnImpl - 	[in,out] If non-null, the spawn implementation.
	///-------------------------------------------------------------------------------------------------

	Spawn(ISpawn* spawnImpl) :
		m_SpawnImpl(spawnImpl)
	{}

	virtual ~Spawn()
	{}

	void SetSpawn(ISpawn* spawnImpl)
	{
		DeleteSpawn();
		this->m_SpawnImpl = spawnImpl;
	}	

	inline SpawnInfo GetFixSpawnInfo() { return this->m_SpawnImpl->GetFixSpawnInfo(); }

	inline SpawnInfo GetRelativeSpawnInfo(float uniform_x, float uniform_y, float uniform_z = 0.0f) { return this->m_SpawnImpl->GetRelativeSpawnInfo(uniform_x, uniform_y, uniform_z); }

	inline SpawnInfo SampleRandomSpawnInfo(RandomSpawnSampler sample = RandomSpawnSampler::Unitform) { return this->m_SpawnImpl->SampleRandomSpawnInfo(sample); }

}; // class Spawn

#endif // __SPAWN_H__