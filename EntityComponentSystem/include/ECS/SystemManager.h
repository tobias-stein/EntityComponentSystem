/*
	Author : Tobias Stein
	Date   : 13th July, 2016
	File   : SystemManager.h
	
	Manager class for systems

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__

#include "API.h"
#include "Engine.h"

#include "ISystem.h"

#include "Memory/Allocator/LinearAllocator.h"
#include "util/FamilyTypeID.h"



namespace ECS
{
	using SystemWorkStateMask	= std::vector<bool>;


	class ECS_API SystemManager : Memory::GlobalMemoryUser
	{
		friend ECSEngine;

		DECLARE_LOGGER

	private:

		using SystemDependencyMatrix = std::vector<std::vector<bool>>;

		using SystemRegistry	= std::unordered_map<u64, ISystem*>;
		using SystemAllocator	= Memory::Allocator::LinearAllocator;

		using SystemWorkOrder	= std::vector<ISystem*>;

		SystemAllocator*		m_SystemAllocator;

		SystemRegistry			m_Systems;

		SystemDependencyMatrix	m_SystemDependencyMatrix;

		SystemWorkOrder			m_SystemWorkOrder;

		// This class is not inteeded to be initialized
		SystemManager(const SystemManager&) = delete;
		SystemManager& operator=(SystemManager&) = delete;	

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void SystemManager::Update(f32 dt_ms);
		///
		/// Summary:	Main update cycle.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	3/10/2017
		///
		/// Parameters:
		/// dt_ms - 	The dt in milliseconds.
		///-------------------------------------------------------------------------------------------------

		void Update(f32 dt_ms);

	public:

		SystemManager();
		~SystemManager();

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T, class... ARGS> T* SystemManager::AddSystem(ARGS&&... systemArgs)
		///
		/// Summary:	Adds a new system.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// T - 	   	Generic type parameter.
		/// ARGS - 	   	Type of the arguments.
		/// Parameters:
		/// systemArgs - 	Variable arguments providing [in,out] The system arguments.
		///
		/// Returns:	Null if it fails, else a pointer to a T.
		///-------------------------------------------------------------------------------------------------

		template<class T, class... ARGS>
		T* AddSystem(ARGS&&... systemArgs)
		{
			const u64 STID = T::STATIC_SYSTEM_TYPE_ID;


			// avoid multiple registrations of the same system
			auto it = this->m_Systems.find(STID);
			if ((this->m_Systems.find(STID) != this->m_Systems.end()) && (it->second != nullptr))
				return (T*)it->second;

			T* system = nullptr;
			void* pSystemMem = this->m_SystemAllocator->allocate(sizeof(T), alignof(T));
			if (pSystemMem != nullptr)
			{

				((T*)pSystemMem)->m_SystemManagerInstance = this;

				// create new system
				system = new (pSystemMem)T(std::forward<ARGS>(systemArgs)...);
				this->m_Systems[STID] = system;

				LogInfo("System \'%s\' (%d bytes) created.", typeid(T).name(), sizeof(T));
			}
			else
			{
				LogError("Unable to create system \'%s\' (%d bytes).", typeid(T).name(), sizeof(T));
				assert(true);
			}

			// resize dependency matrix
			if (STID + 1 > this->m_SystemDependencyMatrix.size())
			{
				this->m_SystemDependencyMatrix.resize(STID + 1);
				for (int i = 0; i < this->m_SystemDependencyMatrix.size(); ++i)
					this->m_SystemDependencyMatrix[i].resize(STID + 1);
			}

			// add to work list
			this->m_SystemWorkOrder.push_back(system);
			
			return system;
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class System_, class... Dependencies> void SystemManager::AddSystemDependency(System_ target,
		/// Dependencies&&... dependencies)
		///
		/// Summary:	Adds a system dependency. This will result in an update of the dependency matrix and re-creation
		/// of the systems working order. This method can be quite costly so use it sparsely.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// System_ - 	   	Type of the system.
		/// Dependencies - 	Type of the dependencies.
		/// Parameters:
		/// target - 	   	Target for the.
		/// dependencies - 	Variable arguments providing [in,out] The dependencies.
		///-------------------------------------------------------------------------------------------------

		template<class System_, class Dependency_>
		void AddSystemDependency(System_ target, Dependency_ dependency)
		{
			const u64 TARGET_ID = target->GetStaticSystemTypeID();
			const u64 DEPEND_ID = dependency->GetStaticSystemTypeID();

			if (this->m_SystemDependencyMatrix[TARGET_ID][DEPEND_ID] != true)
			{
				this->m_SystemDependencyMatrix[TARGET_ID][DEPEND_ID] = true;
				LogInfo("added '%s' as dependency to '%s'", dependency->GetSystemTypeName(), target->GetSystemTypeName())
			}

			//this->UpdateSystemWorkOrder();
		}

		template<class Target_, class Dependency_, class... Dependencies>
		void AddSystemDependency(Target_ target, Dependency_ dependency, Dependencies&&... dependencies)
		{
			const u64 TARGET_ID = target->GetStaticSystemTypeID();
			const u64 DEPEND_ID = dependency->GetStaticSystemTypeID();

			if (this->m_SystemDependencyMatrix[TARGET_ID][DEPEND_ID] != true)
			{
				this->m_SystemDependencyMatrix[TARGET_ID][DEPEND_ID] = true;
				LogInfo("added '%s' as dependency to '%s'", dependency->GetSystemTypeName(), target->GetSystemTypeName())
			}

			this->AddSystemDependency(target, std::forward<Dependencies>(dependencies)...);
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void UpdateSystemWorkOrder();
		///
		/// Summary:	Updates the work order of all systems. This should be called when changed system priorities or adding
		/// new system dependencies.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	3/11/2017
		///-------------------------------------------------------------------------------------------------

		void UpdateSystemWorkOrder();

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T> inline T* SystemManager::GetSystem() const
		///
		/// Summary:	Gets the system.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		///
		/// Returns:	Null if it fails, else the system.
		///-------------------------------------------------------------------------------------------------

		template<class T>
		inline T* GetSystem() const
		{
			auto it = this->m_Systems.find(T::STATIC_SYSTEM_TYPE_ID);

			return it != this->m_Systems.end() ? (T*)it->second : nullptr;
		}


		template<class T>
		void EnableSystem()
		{
			const SystemTypeId STID = T::STATIC_SYSTEM_TYPE_ID;

			// get system
			auto it = this->m_Systems.find(STID);
			if (it != this->m_Systems.end())
			{	
				if (it->second->m_Enabled == true)
					return;

				// enable system
				it->second->m_Enabled = true;
			}
			else
			{
				LogWarning("Trying to enable system [%d], but system is not registered yet.", STID);
			}
		}


		template<class T>
		void DisableSystem()
		{
			const SystemTypeId STID = T::STATIC_SYSTEM_TYPE_ID;

			// get system
			auto it = this->m_Systems.find(STID);
			if (it != this->m_Systems.end())
			{
				if (it->second->m_Enabled == false)
					return;

				// enable system
				it->second->m_Enabled = false;
			}
			else
			{
				LogWarning("Trying to disable system [%d], but system is not registered yet.", STID);
			}
		}

		template<class T>
		void SetSystemUpdateInterval(f32 interval_ms)
		{
			const SystemTypeId STID = T::STATIC_SYSTEM_TYPE_ID;

			// get system
			auto it = this->m_Systems.find(STID);
			if (it != this->m_Systems.end())
			{
				it->second->m_UpdateInterval = interval_ms;
			}
			else
			{
				LogWarning("Trying to change system's [%d] update interval, but system is not registered yet.", STID);
			}
		}

		template<class T>
		void SetSystemPriority(SystemPriority newPriority)
		{
			const SystemTypeId STID = T::STATIC_SYSTEM_TYPE_ID;

			// get system
			auto it = this->m_Systems.find(STID);
			if (it != this->m_Systems.end())
			{
				SystemPriority oldPriority = it->second->m_Priority;

				if (oldPriority == newPriority)
					return;
				
				it->second->m_Priority = newPriority;

				// re-build system work order
				//this->UpdateSystemWorkOrder();
			}
			else
			{
				LogWarning("Trying to change system's [%d] priority, but system is not registered yet.", STID);
			}
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	SystemWorkStateMask SystemManager::GetSystemWorkState() const;
		///
		/// Summary:	Returns the current work state of all systems. The returned state mask can be stored
		/// in local context and reset a later changed working state of systems.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	28/09/2017
		///
		/// Returns:	The system work state.
		///-------------------------------------------------------------------------------------------------

		SystemWorkStateMask GetSystemWorkState() const;

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void SystemManager::SetSystemWorkState(SystemWorkStateMask mask);
		///
		/// Summary:	Resets the current working state of systems by the provided state mask.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	28/09/2017
		///
		/// Parameters:
		/// mask - 	The mask.
		///-------------------------------------------------------------------------------------------------

		void SetSystemWorkState(SystemWorkStateMask mask);

		template<class... ActiveSystems>
		SystemWorkStateMask GenerateActiveSystemWorkState(ActiveSystems&&... activeSystems)
		{
			SystemWorkStateMask mask(this->m_SystemWorkOrder.size(), false);

			std::list<ISystem*> AS = { activeSystems... };
			for (auto s : AS)
			{
				for (int i = 0; i < this->m_SystemWorkOrder.size(); ++i)
				{
					if (this->m_SystemWorkOrder[i]->GetStaticSystemTypeID() == s->GetStaticSystemTypeID())
					{
						mask[i] = true;
						break;
					}
				}
			}

			return mask;
		}
	};

} // namespace ECS

#endif // __SYSTEM_MANAGER_H__