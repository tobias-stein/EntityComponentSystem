///-------------------------------------------------------------------------------------------------
/// File:	LifetimeSystem.h.
///
/// Summary:	Declares the lifetime system class.
///-------------------------------------------------------------------------------------------------

#ifndef __LIFE_TIME_SYSTEM_H__
#define __LIFE_TIME_SYSTEM_H__

#include "GameObject.h"
#include "WorldSystem.h"
#include "LifetimeComponent.h"


class LifetimeSystem : public ECS::System<LifetimeSystem>, public ECS::Event::IEventListener
{
	using ActiveLifetimeComponents = std::list<LifetimeComponent*>;

private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);
	void OnGameObjectSpawned(const GameObjectSpawned* event);
	void OnGameObjectKilled(const GameObjectSpawned* event);

	WorldSystem* m_WorldSystem;

	ActiveLifetimeComponents m_ActiveLifetimeComponents;

public:

	LifetimeSystem();
	virtual ~LifetimeSystem();

	virtual void Update(float dt) override;

}; // class LifetimeSystem 

#endif // __LIFE_TIME_SYSTEM_H__
