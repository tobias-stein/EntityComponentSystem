///-------------------------------------------------------------------------------------------------
/// File:	ControllerComponent.h.
///
/// Summary:	Declares the controller component class.
///-------------------------------------------------------------------------------------------------

#ifndef __CONTROLLER_COMPONENT_H__
#define __CONTROLLER_COMPONENT_H__

#include "Controller.h"

class ControllerComponent : public Controller, public ECS::Component<ControllerComponent>
{
public:

	ControllerComponent(const Controller& controller) : Controller(controller)
	{}

	ControllerComponent(const Controller& controller, const GameObjectId pawn) : Controller(controller)
	{
		assert(this->Possess(pawn) == true && "Unable to possess specified game object!");
	}

	virtual ~ControllerComponent()
	{
		this->Unpossess();
	}


}; // class ControllerComponent

#endif // __CONTROLLER_COMPONENT_H__
