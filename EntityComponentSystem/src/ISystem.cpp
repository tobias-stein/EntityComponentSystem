///-------------------------------------------------------------------------------------------------
/// File:	src\ISystem.cpp.
///
/// Summary:	Declares the ISystem interface.
///-------------------------------------------------------------------------------------------------

#include "ISystem.h"

namespace ECS 
{

	ISystem::ISystem(SystemPriority priority, f32 updateInterval_ms) :
		m_Priority(priority),
		m_UpdateInterval(updateInterval_ms),
		m_Enabled(true)
	{}

	ISystem::~ISystem()
	{}

} // namespace ECS