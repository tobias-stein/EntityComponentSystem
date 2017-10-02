///-------------------------------------------------------------------------------------------------
/// File:	src\EntityManager.cpp.
///
/// Summary:	Implements the entity manager class.
///-------------------------------------------------------------------------------------------------


#include "EntityManager.h"

namespace ECS
{
	EntityManager::EntityManager()
	{
		DEFINE_LOGGER("EntityManager")
		LogInfo("Initialize EntityManager!")
	}

	EntityManager::~EntityManager()
	{
		for (auto ec : this->m_EntityRegistry)
		{
			LogDebug("Releasing remaining entities of type '%s' ...", ec.second->GetEntityContainerTypeName());
			delete ec.second;
			ec.second = nullptr;
		}

		LogInfo("Release EntityManager!")
	}

	EntityId EntityManager::AqcuireEntityId(IEntity* entity)
	{
		return this->m_EntityHandleTable.AqcuireHandle(entity);
	}

	void EntityManager::ReleaseEntityId(EntityId id)
	{
		this->m_EntityHandleTable.ReleaseHandle(id);
	}

} // namespace ECS