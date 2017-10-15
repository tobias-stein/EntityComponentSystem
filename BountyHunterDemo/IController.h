///-------------------------------------------------------------------------------------------------
/// File:	IController.h.
///
/// Summary:	Declares the IController interface. A controller is basically the mechanic that 
/// drives GameObjects. The GameObject itself only exhibits the behaviours like Move, Turn or Jump,
/// but has no will on its own. A controller can take controll (possess) a GameObject and will 
/// function as its brain. There are at least two different controller types. (1) The PlayerController:
/// this controller simply projects the players will onto the GameObject he/she controlls. This can as
/// easy as simply forwarding the player input to the approriate method of th eGameObject. (2) The
/// AIController: this controller has an AI algorithm running in the background that continuesely 
/// monitors the enviroment and react accoding to its stimuly.
///-------------------------------------------------------------------------------------------------

#ifndef __I_CONTROLLER_H__
#define __I_CONTROLLER_H__

#include "GameObject.h"

///-------------------------------------------------------------------------------------------------
/// Class:	IController
///
/// Summary:	This class marks the base controller interface. It provides public methods for 
/// possessing & unpossessing a GameObject as well as updating the controller. Specialized controller
/// like Pthe PlayerController and the AIConroller will derive from this class.
///
/// Author:	Tobias Stein
///
/// Date:	15/10/2017
///-------------------------------------------------------------------------------------------------

class IController
{
public:

	IController()
	{}

	virtual ~IController()
	{}

	virtual bool Possess(const GameObjectId gameObjectId) = 0;

	virtual void Unpossess() = 0;

	virtual GameObjectId GetPossessed() const = 0;

	virtual void Update(float dt) = 0;

}; // class IController

#endif // __I_CONTROLLER_H__
