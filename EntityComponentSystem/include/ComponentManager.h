/*
Author : Tobias Stein
Date   : 7th September, 2017
File   : ComponentManager.h

Manages all component container.

All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#define ECS_MAX_T_COMPONENTS 5000

#include "API.h"

#include "Memory/Allocator/PoolAllocator.h"
#include "ComponentContainer.h"

namespace ECS
{
	class ECS_API ComponentManager : protected Memory::GlobalMemoryUser
	{
		static const u64 MAX_T_COMPONENTS = ECS_MAX_T_COMPONENTS;

		using ComponentAllocator = Memory::Allocator::PoolAllocator;

		using ComponentContainerRegistry = std::unordered_map<ComponentTypeId, Internal::IComponentContainer*>;

		DECLARE_LOGGER

		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(ComponentManager&) = delete;

		ComponentContainerRegistry m_ComponentContainerRegistry;


		template<class T>
		inline Internal::ComponentContainer<T>* GetComponentContainer()
		{
			ComponentTypeId CID = T::STATIC_COMPONENT_TYPE_ID;

			auto it = this->m_ComponentContainerRegistry.find(CID);
			Internal::ComponentContainer<T>* cc = nullptr;

			if (it == this->m_ComponentContainerRegistry.end())
			{
				const size_t memSize = sizeof(T) * ComponentManager::MAX_T_COMPONENTS;

				ComponentAllocator* allocator = new ComponentAllocator(memSize, Allocate(memSize, "ComponentManager"), sizeof(T), alignof(T));

				cc = new Internal::ComponentContainer<T>(allocator, ComponentManager::MAX_T_COMPONENTS);
				this->m_ComponentContainerRegistry[CID] = cc;

				//LogDebug("New component container for \'%s\' created.", typeid(T).name()));
			}
			else
				cc = static_cast<Internal::ComponentContainer<T>*>(it->second);

			assert(cc != nullptr && "Failed to create ComponentContainer<T>!");

			return cc;
		}


	public:
		
		ComponentManager();
		~ComponentManager();

		template<class T, class ...P>
		inline T* AddComponent(P&&... param)
		{
			return GetComponentContainer<T>()->AddComponent(std::forward<P>(param)...);
		}

		// remove component from list
		template<class T>
		inline void RemoveComponent(T* const component)
		{
			// TODO!
			//Internal::ComponentContainer<T>* cc = static_cast<Internal::ComponentContainer<T>*>(this->m_ComponentContainerRegistry[T::STATIC_COMPONENT_TYPE_ID]);
			//if(cc != nullptr)
			//	cc->remove(component);
		}

		// get component list
		template<class T>
		inline ComponentList<T>& const GetComponentList()
		{
			return GetComponentContainer<T>()->GetComponentList();
		}

	}; // ComponentManager


} // namespace ECS

#endif // __COMPONENT_MANAGER_H__