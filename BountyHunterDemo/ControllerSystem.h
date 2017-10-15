///-------------------------------------------------------------------------------------------------
/// File:	ControllerSystem.h.
///
/// Summary:	Declares the controller system class.
///-------------------------------------------------------------------------------------------------

#ifndef __CONTROLLER_SYSTEM_H__
#define __CONTROLLER_SYSTEM_H__

#include <ECS/ECS.h>

#include "ControllerComponent.h"

class ControllerSystem : public ECS::System<ControllerSystem>, public ECS::Event::IEventListener
{
	using RegisteredController = std::list<ControllerComponent*>;

private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);

	RegisteredController m_Controller;

public:

	ControllerSystem();
	virtual ~ControllerSystem();

	virtual void Update(float dt) override;

}; // class ControllerSystem

#endif // __CONTROLLER_SYSTEM_H__
