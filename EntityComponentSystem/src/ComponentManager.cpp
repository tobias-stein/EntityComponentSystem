/*
	Author : Tobias Stein
	Date   : 7th September, 2017
	File   : ComponentManager.cpp
	
	Manages all component container.

	All Rights Reserved. (c) Copyright 2016.
*/


#include "ComponentManager.h"

namespace ECS {

	ComponentManager::ComponentManager()
	{
		DEFINE_LOGGER("ComponentManager")
		LogInfo("Initialize ComponentManager!");

		const size_t NUM_COMPONENTS { util::Internal::FamilyTypeID<IComponent>::Get() };

		this->m_EntityComponentMap.resize(ENITY_LUT_GROW);
		for (auto i = 0; i < ENITY_LUT_GROW; ++i)
			this->m_EntityComponentMap[i].resize(NUM_COMPONENTS, INVALID_COMPONENT_ID);
	}

	ComponentManager::~ComponentManager()
	{
		for (auto cc : this->m_ComponentContainerRegistry)
		{
			LogDebug("Releasing remaining entities of type '%s' ...", cc.second->GetComponentContainerTypeName());
			delete cc.second;
			cc.second = nullptr;
		}
	
		LogInfo("Release ComponentManager!");
	}

	ComponentId ComponentManager::AqcuireComponentId(IComponent* component)
	{
		int i = 0;
		for (; i < this->m_ComponentLUT.size(); ++i)
		{
			if (this->m_ComponentLUT[i] == nullptr)
			{
				this->m_ComponentLUT[i] = component;
				return i;
			}
		}

		// increase component LUT size
		this->m_ComponentLUT.resize(this->m_ComponentLUT.size() + COMPONENT_LUT_GROW, nullptr);

		this->m_ComponentLUT[i] = component;
		return i;
	}

	void ComponentManager::ReleaseComponentId(ComponentId id)
	{
		assert((id != INVALID_COMPONENT_ID && id < this->m_ComponentLUT.size()) && "Invalid component id");
		this->m_ComponentLUT[id] = nullptr;
	}

	void ComponentManager::MapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId)
	{
		static const size_t NUM_COMPONENTS { util::Internal::FamilyTypeID<IComponent>::Get() };

		if ((this->m_EntityComponentMap.size() - 1) < entityId.index)
		{
			size_t oldSize = this->m_EntityComponentMap.size();

			// we scale this map size along the entity lookup table size
			size_t newSize = oldSize + ENITY_LUT_GROW;
			
			this->m_EntityComponentMap.resize(newSize);

			for (auto i = oldSize; i < newSize; ++i)
				this->m_EntityComponentMap[i].resize(NUM_COMPONENTS, INVALID_COMPONENT_ID);
		}

		// create mapping
		this->m_EntityComponentMap[entityId.index][componentTypeId] = componentId;
	}

	void ComponentManager::UnmapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId)
	{
		assert(this->m_EntityComponentMap[entityId.index][componentTypeId] == componentId && "FATAL: Entity Component ID mapping corruption!");

		// free mapping
		this->m_EntityComponentMap[entityId.index][componentTypeId] = INVALID_COMPONENT_ID;

		// free component id
		this->ReleaseComponentId(componentId);
	}

} // namespace ECS