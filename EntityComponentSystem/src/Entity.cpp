/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : Entity.cpp
	
	Entity class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Entity.h"
#include "IComponent.h"
#include "util/FamilyTypeCounter.h"

namespace ECS
{

	Log::Logger* Entity::s_Logger = GetLogger("EntityManager");

	// first valid entity id
	EntityId Entity::s_NextValidEntityId{ 0u };

	Entity::Entity() :
		m_Id(Entity::s_NextValidEntityId++),
		m_ComponentBitMask(util::Internal::FamilyTypeCounter<IComponent>::Get()),
		m_Components(util::Internal::FamilyTypeCounter<IComponent>::Get()),
		m_Active(true)
	{
		s_Logger->LogDebug("Create new Entity [ENTITY-ID: %d]", m_Id);
		
		// At this point all implemented component types will have there id set,
		// because they are declared static

		for (int i = 0; i < util::Internal::FamilyTypeCounter<IComponent>::Get(); ++i)
		{
			this->m_ComponentBitMask[i] = false;
			this->m_Components[i] = nullptr;
		}
	}

	Entity::~Entity()
	{
		s_Logger->LogDebug("Destroy Entity [ENTITY-ID: %d]", m_Id);

		this->m_ComponentBitMask.clear();
		this->m_Components.clear();
	}
}