/*
	Author : Tobias Stein
	Date   : 13th July, 2016
	File   : SystemManager.cpp
	
	Manager class for systems

	All Rights Reserved. (c) Copyright 2016.
*/

#include "SystemManager.h"
#include "ISystem.h"

namespace ECS
{
	SystemManager::SystemManager()
	{
		DEFINE_LOGGER("SystemManager")

		LogInfo("Initialize SystemManager!");

		// acquire global memory
		this->m_SystemAllocator = new SystemAllocator(SystemManager::SYSTEM_MEMORY_CAPACITY, Allocate(SystemManager::SYSTEM_MEMORY_CAPACITY, "SystemManager"));

		this->m_Systems.resize(util::Internal::FamilyTypeCounter<ISystem>::Get());

		for (auto system : this->m_Systems)
			system = nullptr;
	}

	SystemManager::~SystemManager()
	{
		for (auto system : this->m_Systems)
		{
			system->~ISystem();
			system = nullptr;
		}

		// free allocated global memory
		Free((void*)this->m_SystemAllocator->GetFirstMemoryAddress());
		delete this->m_SystemAllocator;
		this->m_SystemAllocator = nullptr;

		m_Systems.clear();

		LogInfo("Realse SystemManager!");
	}

} // namespace ECS