/*
	Author : Tobias Stein
	Date   : 13th July, 2016
	File   : SystemManager.h
	
	Manager class for systems

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __SYSTEM_MANAGER_H__
#define __SYSTEM_MANAGER_H__

#define ECS_SYSTEM_MEMORY_CAPACITY	8192 // 8Mb

#include "API.h"
#include "Engine.h"

#include "ISystem.h"

#include "Memory/Allocator/LinearAllocator.h"
#include "util/FamilyTypeCounter.h"



namespace ECS
{
	///-------------------------------------------------------------------------------------------------
	/// Struct:	SystemCreated
	///
	/// Summary:	Sent when new system was created.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	30/09/2017
	///-------------------------------------------------------------------------------------------------

	struct SystemCreated : public Event::Event<SystemCreated>
	{
		SystemTypeId m_SystemTypeID;

		SystemCreated(SystemTypeId systemTypeId) :
			m_SystemTypeID(systemTypeId)
		{}

	}; // struct SystemCreated 

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

		static const size_t SYSTEM_MEMORY_CAPACITY = ECS_SYSTEM_MEMORY_CAPACITY;

		SystemAllocator*		m_SystemAllocator;

		SystemRegistry			m_Systems;

		SystemDependencyMatrix	m_SystemDependencyMatrix;

		SystemWorkOrder			m_SystemWorkOrder;

		// This class is not inteeded to be initialized
		SystemManager(const SystemManager&) = delete;
		SystemManager& operator=(SystemManager&) = delete;	

		void UpdateSystemWorkOrder();

		void Update();

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
			if (this->m_Systems.find(STID) != this->m_Systems.end())
				return (T*)it->second;

			T* system = nullptr;
			void* pSystemMem = this->m_SystemAllocator->allocate(sizeof(T), alignof(T));
			if (pSystemMem != nullptr)
			{
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

			// Broadcast SystemCreated event
			ECS_Engine->ECS_EventHandler->Send<SystemCreated>(STID);

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

		template<class System_, class... Dependencies>
		void AddSystemDependency(System_ target, Dependencies&&... dependencies)
		{
			const u64 TARGET_ID = target->GetStaticSystemTypeID();

			auto D = { dependencies... };

			bool changed = false;

			for (auto d : D)
			{
				if (this->m_SystemDependencyMatrix[TARGET_ID][d->GetStaticSystemTypeID()] == true)
					continue;

				this->m_SystemDependencyMatrix[TARGET_ID][d->GetStaticSystemTypeID()] = true;
				LogInfo("added '%s' as dependency to '%s'", d->GetSystemTypeName(), target->GetSystemTypeName())
				
				changed = true;
			}

			// update work order
			if(changed == true)
				this->UpdateSystemWorkOrder();
		}

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
	};

} // namespace ECS

#endif // __SYSTEM_MANAGER_H__