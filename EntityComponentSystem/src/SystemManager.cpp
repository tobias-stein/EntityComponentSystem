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
	}

	SystemManager::~SystemManager()
	{
		for (auto system : this->m_Systems)
		{
			system.second->~ISystem();
			system.second = nullptr;
		}

		m_Systems.clear();

		// free allocated global memory
		Free((void*)this->m_SystemAllocator->GetMemoryAddress0());
		delete this->m_SystemAllocator;
		this->m_SystemAllocator = nullptr;
		
		LogInfo("Release SystemManager!");
	}

	void SystemManager::Update()
	{
		for (ISystem* system : this->m_SystemWorkOrder)
		{
			system->Tick(TIME_STEP);
		}
	}

	void SystemManager::UpdateSystemWorkOrder()
	{
		const size_t NUM_SYSTEMS = this->m_SystemDependencyMatrix.size();

		std::vector<int> numDependencies(NUM_SYSTEMS, 0);

		for (int i = 0; i < NUM_SYSTEMS; ++i)
		{
			for (int j = 0; j < NUM_SYSTEMS; ++j)
			{
				if (this->m_SystemDependencyMatrix[i][j] == true)
					numDependencies[i]++;
			}
		}

		std::vector<int> noDependencyStack;

		// initial round, collect all vertices without dependencies
		for (int i = 0; i < NUM_SYSTEMS; ++i)
		{
			if (numDependencies[i] == 0)
			{
				noDependencyStack.push_back(i);
				numDependencies[i] = -1;
			}
		}

		// cycle check:
		if (noDependencyStack.empty() == true)
			assert(false && "System dependencies contain a cycle!");


		std::vector<int> topologicalOrder;

		// do Kahn's algorithm
		while (noDependencyStack.empty() == false)
		{
			int i = noDependencyStack.back();
			noDependencyStack.pop_back();

			topologicalOrder.push_back(i);

			for (int j = 0; j < NUM_SYSTEMS; ++j)
			{
				if (this->m_SystemDependencyMatrix[j][i] == true)
					numDependencies[j]--;

				if (numDependencies[j] == 0)
				{
					noDependencyStack.push_back(j);
					numDependencies[j] = -1;
				}
			}
		}

		// cycle check:
		for (int i = 0; i < NUM_SYSTEMS; ++i)
			if (numDependencies[i] > 0)
				assert(false && "System dependencies contain a cycle!");

		LogInfo("Update system work order:")

		// re-build system work order
		this->m_SystemWorkOrder.clear();

		for (int i = 0; i < topologicalOrder.size(); ++i)
		{
			this->m_SystemWorkOrder.push_back(this->m_Systems[topologicalOrder[i]]);
			LogInfo("\t%d: %s", i + 1, this->m_Systems[topologicalOrder[i]]->GetSystemTypeName())
		}
	}

} // namespace ECS