/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : Entity.cpp
	
	Entity class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Entity.h"
#include "IComponent.h"
#include "util/StaticTypeCounter.h"

namespace ECS
{
	// first valid entity id
	EntityId Entity::s_NextValidEntityId{ 0u };

	Entity::Entity() :
		m_Id(Entity::s_NextValidEntityId++),
		m_ComponentBitMask(util::StaticTypeCounter<IComponent>::Get()),
		m_Components(util::StaticTypeCounter<IComponent>::Get()),
		m_Active(true)
	{
		Log::Logger::GetInstance().LogDebug("Create new Entity [ENTITY-ID: %d]", m_Id);
		
		// At this point all implemented component types will have there id set,
		// because they are declared static

		for (int i = 0; i < util::StaticTypeCounter<IComponent>::Get(); ++i)
		{
			this->m_ComponentBitMask[i] = false;
			this->m_Components[i] = nullptr;
		}
	}

	Entity::~Entity()
	{
		Log::Logger::GetInstance().LogDebug("Destroy Entity [ENTITY-ID: %d]", m_Id);

		this->m_ComponentBitMask.clear();
		this->m_Components.clear();
	}
}