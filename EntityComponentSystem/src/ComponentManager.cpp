/*
	Author : Tobias Stein
	Date   : 7th September, 2017
	File   : ComponentManager.cpp
	
	Manages all component container.

	All Rights Reserved. (c) Copyright 2016.
*/


#include "ComponentManager.h"

namespace ECS {


	ComponentManager::ComponentManager() : 
		m_Logger(GetLogger("ComponentManager")),
		m_ComponentContainerRegistry(util::Internal::FamilyTypeCounter<IComponent>::Get())
	{
		m_Logger->LogInfo("Initialize ComponentManager!");
	}

	ComponentManager::~ComponentManager()
	{
		for (auto cc : this->m_ComponentContainerRegistry)
		{
			cc->~IComponentContainer();
			cc = nullptr;
		}


		m_Logger->LogInfo("Realse ComponentManager!");
	}

} // namespace ECS