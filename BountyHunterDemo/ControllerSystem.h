///-------------------------------------------------------------------------------------------------
/// File:	ControllerSystem.h.
///
/// Summary:	Declares the controller system class.
///-------------------------------------------------------------------------------------------------

#ifndef __CONTROLLER_SYSTEM_H__
#define __CONTROLLER_SYSTEM_H__

#include <ECS/ECS.h>

#include "Controller.h"

class ControllerSystem : public ECS::System<ControllerSystem>, public ECS::Event::IEventListener
{
	using RegisteredController = std::list<Controller*>;

private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	RegisteredController m_Controller;

public:

	ControllerSystem();
	virtual ~ControllerSystem();

	virtual void Update(float dt) override;

	void RegisterController(Controller* controller);
	void UnregisterController(Controller* controller);

}; // class ControllerSystem

#endif // __CONTROLLER_SYSTEM_H__
