///-------------------------------------------------------------------------------------------------
/// File:	src\EntityManager.cpp.
///
/// Summary:	Implements the entity manager class.
///-------------------------------------------------------------------------------------------------


#include "EntityManager.h"

namespace ECS
{
	EntityManager::EntityManager() :
		m_EntityLUT(ENITY_LUT_GROW, nullptr)
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

	EntityId EntityManager::AqcuireEntityId()
	{
		int i = 0;
		for (; i < this->m_EntityLUT.size(); ++i)
		{
			if (this->m_EntityLUT[i] == nullptr)
				return i;
		}

		// increase entity LUT size
		this->m_EntityLUT.resize(this->m_EntityLUT.size() + ENITY_LUT_GROW, nullptr);

		return i;
	}

	void EntityManager::ReleaseEntityId(EntityId id)
	{
		assert((id != INVALID_ENTITY_ID && id < this->m_EntityLUT.size()) && "Invalid entity id");
		this->m_EntityLUT[id] = nullptr;
	}

} // namespace ECS