///-------------------------------------------------------------------------------------------------
/// File:	src\ISystem.cpp.
///
/// Summary:	Declares the ISystem interface.
///-------------------------------------------------------------------------------------------------

#include "ISystem.h"
#include "Engine.h"

namespace ECS 
{

	ISystem::ISystem(SystemPriority priority) :
		m_Priority(priority),
		m_Enabled(true)
	{}

	ISystem::~ISystem()
	{}

	void ISystem::SetActive(bool state)
	{
		if (state == this->m_Enabled)
			return;

		// set state
		this->m_Enabled = state;

		// broadcast event
		if(state == true)
			ECS_Engine->ECS_EventHandler->Send<SystemEnabled>(this->GetStaticSystemTypeID());
		else
			ECS_Engine->ECS_EventHandler->Send<SystemDisabled>(this->GetStaticSystemTypeID());
	}

} // namespace ECS