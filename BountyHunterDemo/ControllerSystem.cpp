///-------------------------------------------------------------------------------------------------
/// File:	ControllerSystem.cpp.
///
/// Summary:	Implements the controller system class.
///-------------------------------------------------------------------------------------------------

#include "ControllerSystem.h"

ControllerSystem::ControllerSystem()
{
	RegisterEventCallbacks();
}

ControllerSystem::~ControllerSystem()
{
	UnregisterEventCallbacks();
}

void ControllerSystem::Update(float dt)
{
	for (auto C : this->m_Controller)
	{
		C->Update(dt);
	}
}

void ControllerSystem::RegisterController(Controller* controller)
{
	this->m_Controller.push_back(controller);
}

void ControllerSystem::UnregisterController(Controller* controller)
{
	this->m_Controller.remove(controller);
}

void ControllerSystem::RegisterEventCallbacks()
{
}

void ControllerSystem::UnregisterEventCallbacks()
{
}


