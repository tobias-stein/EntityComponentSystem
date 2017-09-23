/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : Entity.cpp
	
	Entity class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "IEntity.h"
#include "EntityManager.h"
#include "IComponent.h"
#include "util/FamilyTypeCounter.h"

namespace ECS
{
	DEFINE_STATIC_LOGGER(IEntity, "Entity")
		
	IEntity::IEntity() :
		m_Id(INVALID_ENTITY_ID),
		m_ComponentBitMask(util::Internal::FamilyTypeCounter<IComponent>::Get()),
		m_Components(util::Internal::FamilyTypeCounter<IComponent>::Get()),
		m_Active(true)
	{		
		// At this point all implemented component types will have there id set,
		// because they are declared static

		for (int i = 0; i < util::Internal::FamilyTypeCounter<IComponent>::Get(); ++i)
		{
			this->m_ComponentBitMask[i] = false;
			this->m_Components[i] = nullptr;
		}
	}

	IEntity::~IEntity()
	{
		this->m_ComponentBitMask.clear();
		this->m_Components.clear();
	}
}