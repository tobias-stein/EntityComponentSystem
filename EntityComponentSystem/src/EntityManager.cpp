///-------------------------------------------------------------------------------------------------
/// File:	src\EntityManager.cpp.
///
/// Summary:	Implements the entity manager class.
///-------------------------------------------------------------------------------------------------


#include "EntityManager.h"

namespace ECS
{
	EntityManager::EntityManager() :
		m_PendingDestroyedEntities(1024),
		m_NumPendingDestroyedEntities(0)
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

	void EntityManager::RemoveDestroyedEntities()
	{
		for (size_t i = 0; i < this->m_NumPendingDestroyedEntities; ++i)
		{
			EntityId entityId = this->m_PendingDestroyedEntities[i];

			IEntity* entity = this->m_EntityHandleTable[entityId];

			const EntityTypeId ETID = entity->GetStaticEntityTypeID();

			// get appropriate entity container and destroy entity
			auto it = this->m_EntityRegistry.find(ETID);
			if (it != this->m_EntityRegistry.end())
			{
				// release entity's components
				ECS_Engine->ECS_ComponentManager->RemoveAllComponents(entityId);

				it->second->DestroyEntity(entity);
			}
		}

		this->m_NumPendingDestroyedEntities = 0;
	}

} // namespace ECS