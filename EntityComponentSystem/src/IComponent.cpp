///-------------------------------------------------------------------------------------------------
/// File:	src\IComponent.cpp.
///
/// Summary:	Declares the IComponent interface.
///-------------------------------------------------------------------------------------------------

#include "IComponent.h"

namespace ECS
{
	IComponent::IComponent() :	
		m_Owner(INVALID_ENTITY_ID),
		m_Enabled(true)
	{}

	IComponent::~IComponent()
	{}

} // namespace ECS