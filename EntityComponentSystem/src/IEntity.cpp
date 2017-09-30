/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : Entity.cpp
	
	Entity class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "IEntity.h"
#include "Engine.h"
#include "EntityManager.h"

namespace ECS
{
	DEFINE_STATIC_LOGGER(IEntity, "Entity")
		
	IEntity::IEntity() :
		m_Active(true)
	{
		// aqcuire a new unique enity id from EntityManager
		this->m_EntityID = ECS_Engine->ECS_EntityManager->AqcuireEntityId(this);
	}

	IEntity::~IEntity()
	{
		// release id so it can be reused
		ECS_Engine->ECS_EntityManager->ReleaseEntityId(this->m_EntityID);
	}
}