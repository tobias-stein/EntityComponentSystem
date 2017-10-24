///-------------------------------------------------------------------------------------------------
/// File:	SpawnComponent.h.
///
/// Summary:	Declares the spawn componenth class.
///-------------------------------------------------------------------------------------------------

#ifndef __SPAWN_COMPONENT_H__
#define __SPAWN_COMPONENT_H__

#include <ECS/ECS.h>
#include "Spawn.h"

class SpawnComponent : public ECS::Component<SpawnComponent>
{
private:

	Spawn m_Spawn;

public:

	SpawnComponent(const Spawn& spawn);
	virtual ~SpawnComponent();

	inline Spawn& GetSpawn() { return this->m_Spawn; }

}; // class SpawnComponent

#endif // __SPAWN_COMPONENT_H__