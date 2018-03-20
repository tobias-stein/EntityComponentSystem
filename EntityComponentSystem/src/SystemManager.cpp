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
		this->m_SystemAllocator = new SystemAllocator(ECS_SYSTEM_MEMORY_BUFFER_SIZE, Allocate(ECS_SYSTEM_MEMORY_BUFFER_SIZE, "SystemManager"));
	}
	
	SystemManager::~SystemManager()
	{		
		for (SystemWorkOrder::reverse_iterator it = this->m_SystemWorkOrder.rbegin(); it != this->m_SystemWorkOrder.rend(); ++it)
		{
			(*it)->~ISystem();
			*it = nullptr;
		}

		m_SystemWorkOrder.clear();
		m_Systems.clear();

		// free allocated global memory
		Free((void*)this->m_SystemAllocator->GetMemoryAddress0());
		delete this->m_SystemAllocator;
		this->m_SystemAllocator = nullptr;
		
		LogInfo("Release SystemManager!");
	}

	void SystemManager::Update(f32 dt_ms)
	{
		for (ISystem* system : this->m_SystemWorkOrder)
		{
			// increase interval since last update
			system->m_TimeSinceLastUpdate += dt_ms;

			// check systems update state
			system->m_NeedsUpdate = (system->m_UpdateInterval < 0.0f) || ((system->m_UpdateInterval > 0.0f) && (system->m_TimeSinceLastUpdate > system->m_UpdateInterval));

			if (system->m_Enabled == true && system->m_NeedsUpdate == true)
			{			
				system->PreUpdate(dt_ms);	
			}
		}

		for (ISystem* system : this->m_SystemWorkOrder)
		{
			if (system->m_Enabled == true && system->m_NeedsUpdate == true)
			{
				system->Update(dt_ms);

				// reset interval
				system->m_TimeSinceLastUpdate = 0.0f;
			}
		}

		for (ISystem* system : this->m_SystemWorkOrder)
		{
			if (system->m_Enabled == true && system->m_NeedsUpdate == true)
			{
				system->PostUpdate(dt_ms);
			}
		}
	}

	void SystemManager::UpdateSystemWorkOrder()
	{
		// depth-first-search function
		static const std::function<void(SystemTypeId, std::vector<int>&, const std::vector<std::vector<bool>>&, std::vector<SystemTypeId>&)> DFS = [&](SystemTypeId vertex, std::vector<int>& VERTEX_STATE, const std::vector<std::vector<bool>>& EDGES, std::vector<SystemTypeId>& output)
		{
			VERTEX_STATE[vertex] = 1; // visited

			for (int i = 0; i < VERTEX_STATE.size(); ++i)
			{
				if (EDGES[i][vertex] == true && VERTEX_STATE[i] == 0)
					DFS(i, VERTEX_STATE, EDGES, output);
			}

			VERTEX_STATE[vertex] = 2; // done
			output.push_back(vertex);
		};

		const size_t NUM_SYSTEMS = this->m_SystemDependencyMatrix.size();


		// create index array
		std::vector<int> INDICES(NUM_SYSTEMS);
		for (int i = 0; i < NUM_SYSTEMS; ++i)
			INDICES[i] = i;

		// determine vertex-groups
		std::vector<std::vector<SystemTypeId>>	VERTEX_GROUPS;
		std::vector<SystemPriority>				GROUP_PRIORITY;

		while (INDICES.empty() == false)
		{
			SystemTypeId index = INDICES.back();
			INDICES.pop_back();

			if (index == -1)
				continue;

			std::vector<SystemTypeId> group;
			std::vector<SystemTypeId> member;

			SystemPriority groupPriority = LOWEST_SYSTEM_PRIORITY;
			member.push_back(index);

			while (member.empty() == false)
			{
				index = member.back();
				member.pop_back();

				for (int i = 0; i < INDICES.size(); ++i)
				{
					if (INDICES[i] != -1 && (this->m_SystemDependencyMatrix[i][index] == true || this->m_SystemDependencyMatrix[index][i] == true))
					{
						member.push_back(i);
						INDICES[i] = -1;
					}
				}

				group.push_back(index);


				ISystem* sys = this->m_Systems[index];
				groupPriority = std::max((sys != nullptr ? sys->m_Priority : NORMAL_SYSTEM_PRIORITY), groupPriority);
			}

			VERTEX_GROUPS.push_back(group);
			GROUP_PRIORITY.push_back(groupPriority);
		}

		const size_t NUM_VERTEX_GROUPS = VERTEX_GROUPS.size();

		// do a topological sort on groups w.r.t. to groups priority!
		std::vector<int> vertex_states(NUM_SYSTEMS, 0);

		std::multimap<SystemPriority, std::vector<SystemTypeId>> VERTEX_GROUPS_SORTED;


		for (int i = 0; i < NUM_VERTEX_GROUPS; ++i)
		{
			auto g = VERTEX_GROUPS[i];

			std::vector<SystemTypeId> order;

			for (int i = 0; i < g.size(); ++i)
			{
				if (vertex_states[g[i]] == 0)
					DFS(g[i], vertex_states, this->m_SystemDependencyMatrix, order);
			}

			std::reverse(order.begin(), order.end());
			
			// note: MAX - PRIORITY will frce the correct sorting behaviour in multimap (by default a multimap sorts int values from low to high)
			VERTEX_GROUPS_SORTED.insert(std::pair<SystemPriority, std::vector<SystemTypeId>>(std::numeric_limits<SystemPriority>::max() - GROUP_PRIORITY[i], order));
		}



		LogInfo("Update system work order:")

		// re-build system work order
		this->m_SystemWorkOrder.clear();
		for (auto group : VERTEX_GROUPS_SORTED)
		{
			for (auto m : group.second)
			{
				ISystem* sys = this->m_Systems[m];
				if (sys != nullptr)
				{
					this->m_SystemWorkOrder.push_back(sys);
					LogInfo("\t%s", sys->GetSystemTypeName())
				}
			}
		}
	}

	SystemWorkStateMask SystemManager::GetSystemWorkState() const
	{
		SystemWorkStateMask mask(this->m_SystemWorkOrder.size());

		for (int i = 0; i < this->m_SystemWorkOrder.size(); ++i)
		{
			mask[i] = this->m_SystemWorkOrder[i]->m_Enabled;
		}

		return mask;
	}

	void SystemManager::SetSystemWorkState(SystemWorkStateMask mask) 
	{
		assert(mask.size() == this->m_SystemWorkOrder.size() && "Provided mask does not match size of current system array.");

		for (int i = 0; i < this->m_SystemWorkOrder.size(); ++i)
		{
			this->m_SystemWorkOrder[i]->m_Enabled = mask[i];
		}
	}

} // namespace ECS
