///-------------------------------------------------------------------------------------------------
/// File:	Controller.h.
///
/// Summary:	Declares the controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "PlayerController.h"
//#include "AIController.h"

class Controller
{
private:

	IController*	m_ControllerImpl;

public:

	Controller(IController* controllerImpl);

	~Controller();

	void SetController(IController* controllerImpl);

	bool SwapController(IController* controllerImpl);

	bool Possess(const GameObjectId gameObjectId);

	void Unpossess();

	GameObjectId GetPossessed();

	void Update(float dt);

}; // class Controller

#endif // __CONTROLLER_H__
