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

} // namespace ECS