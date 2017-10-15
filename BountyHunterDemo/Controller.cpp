///-------------------------------------------------------------------------------------------------
/// File:	Controller.cpp.
///
/// Summary:	Implements the controller class.
///-------------------------------------------------------------------------------------------------

#include "Controller.h"

Controller::Controller(IController* controllerImpl) :
	m_ControllerImpl(controllerImpl)
{}

Controller::~Controller()
{
	this->m_ControllerImpl = nullptr;
}

void Controller::Release()
{
	if (this->m_ControllerImpl != nullptr)
	{
		delete this->m_ControllerImpl;
		this->m_ControllerImpl = nullptr;
	}
}

void Controller::SetController(IController* controllerImpl)
{
	if(this->m_ControllerImpl != nullptr)
		this->m_ControllerImpl->Unpossess();

	this->m_ControllerImpl = controllerImpl;
}

bool Controller::SwapController(IController* controllerImpl)
{
	if (controllerImpl == nullptr)
		return false;

	GameObjectId pawnID = INVALID_GAMEOBJECT_ID;
	
	if (this->m_ControllerImpl != nullptr)
	{
		pawnID = this->m_ControllerImpl->GetPossessed();
		this->m_ControllerImpl->Unpossess();
	}

	this->m_ControllerImpl = controllerImpl;

	if (pawnID == INVALID_GAMEOBJECT_ID)
		return false;

	return this->m_ControllerImpl->Possess(pawnID);
}

bool Controller::Possess(const GameObjectId gameObjectId) 
{ 
	if (this->m_ControllerImpl == nullptr)
		return false;

	return this->m_ControllerImpl->Possess(gameObjectId); 
}

void Controller::Unpossess() 
{ 
	if (this->m_ControllerImpl == nullptr)
		return;

	this->m_ControllerImpl->Unpossess(); 
}

GameObjectId Controller::GetPossessed() 
{ 
	if (this->m_ControllerImpl == nullptr)
		return INVALID_GAMEOBJECT_ID;

	return this->m_ControllerImpl->GetPossessed(); 
}

void Controller::Update(float dt) 
{ 
	if (this->m_ControllerImpl == nullptr)
		return;

	this->m_ControllerImpl->Update(dt); 
}