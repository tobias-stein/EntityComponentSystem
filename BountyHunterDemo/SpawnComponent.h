///-------------------------------------------------------------------------------------------------
/// File:	SpawnComponent.h.
///
/// Summary:	Declares the spawn componenth class.
///-------------------------------------------------------------------------------------------------

#ifndef __SPAWN_COMPONENT_H__
#define __SPAWN_COMPONENT_H__

#include <ECS/ECS.h>
#include "Spawn.h"

class SpawnComponent : public Spawn, public ECS::Component<SpawnComponent>
{
public:

	SpawnComponent(const Spawn& spawn);
	virtual ~SpawnComponent();

}; // class SpawnComponent

#endif // __SPAWN_COMPONENT_H__