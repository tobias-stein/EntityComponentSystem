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

#include "Memory/Allocator/LinearAllocator.h"
#include "util/FamilyTypeCounter.h"



namespace ECS
{

	// forward declaration
	class ISystem;

	class ECS_API SystemManager : Memory::GlobalMemoryUser
	{
		friend ECSEngine;

		DECLARE_LOGGER

	private:

		using SystemDependencyMatrix = std::vector<std::vector<bool>>;

		using SystemRegistry	= std::unordered_map<u64, ISystem*>;
		using SystemAllocator	= Memory::Allocator::LinearAllocator;

		using SystemWorkOrder = std::vector<ISystem*>;

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


			return system;
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class System_, class... Dependencies> void SystemManager::AddSystemDependency(System_ target,
		/// Dependencies&&... dependencies)
		///
		/// Summary:	Adds a system dependenc. This will result in an update of the dependency matrix.
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

			LogInfo("Add new %d dependencies for \'%s\':", sizeof...(dependencies), target->GetSystemTypeName())
			for (auto d : D)
			{
				this->m_SystemDependencyMatrix[TARGET_ID][d->GetStaticSystemTypeID()] = true;
				LogInfo("\tadd '%s' as dependency", d->GetSystemTypeName())
			}

			// update work order
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
	};

} // namespace ECS

#endif // __SYSTEM_MANAGER_H__