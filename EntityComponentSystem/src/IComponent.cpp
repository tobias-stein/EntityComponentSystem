///-------------------------------------------------------------------------------------------------
/// File:	src\IComponent.cpp.
///
/// Summary:	Declares the IComponent interface.
///-------------------------------------------------------------------------------------------------

#include "IComponent.h"
#include "Engine.h"
#include "ComponentManager.h"

namespace ECS
{
	IComponent::IComponent() :	
		m_Owner(INVALID_ENTITY_ID),
		m_Enabled(true)
	{
		// aqcuire new unique component id
		this->m_ComponentID = ECS_Engine->ECS_ComponentManager->AqcuireComponentId(this);
	}

	IComponent::~IComponent()
	{
		// release id so it can be reused
		ECS_Engine->ECS_ComponentManager->ReleaseComponentId(this->m_ComponentID);
	}

} // namespace ECS