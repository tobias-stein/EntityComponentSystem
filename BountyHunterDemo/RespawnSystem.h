///-------------------------------------------------------------------------------------------------
/// File:	RespawnSystem.h.
///
/// Summary:	Declares the respawn system class.
///-------------------------------------------------------------------------------------------------

#ifndef __RESPAWN_SYSTEM_H__
#define __RESPAWN_SYSTEM_H__

#include <ECS/ECS.h>

#include "WorldSystem.h"
#include "RespawnComponent.h"

class RespawnSystem : public ECS::System<RespawnSystem>, protected ECS::Event::IEventListener
{
private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectKilled(const GameObjectCreated* event);

public:

	RespawnSystem();
	virtual ~RespawnSystem();

	virtual void Update(float dt);

}; // class RespawnSystem

#endif // __RESPAWN_SYSTEM_H__
