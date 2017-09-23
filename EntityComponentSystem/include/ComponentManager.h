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

#include "Component.h"


namespace ECS
{
	class ECS_API ComponentManager : Memory::GlobalMemoryUser
	{

		template<class T>
		using ComponentList = std::list<T*>;

		class IComponentContainer
		{
		public:
		
			virtual ~IComponentContainer()
			{}
		};
		
		template<class T>
		class ComponentContainer : public IComponentContainer
		{
		private:
		
			using ComponentAllocator = Memory::Allocator::PoolAllocator;
		
			using TComponentList = ComponentList<T>;
		
			const size_t MAX_COMPONENTS;
		
			DECLARE_LOGGER
		
			ComponentAllocator* m_ComponentAllocator;
		
			TComponentList m_Components;
		
			ComponentContainer(const ComponentContainer&) = delete;
			ComponentContainer& operator=(ComponentContainer&) = delete;
		
		public:
		
			ComponentContainer(ComponentAllocator* allocator, const size_t maxComponents) :
				m_ComponentAllocator(allocator),
				MAX_COMPONENTS(maxComponents)
			{
				DEFINE_LOGGER("ComponentManager")
			}
		
			~ComponentContainer()
			{
				LogInfo("Destroy \'%s\' components ...", typeid(T).name());
		
				for (auto component : this->m_Components)
				{
					((IComponent*)component)->~IComponent();
					component = nullptr;
				}
		
				this->m_Components.clear();
			}
		
		
			// Add component to listinline void AddComponent(T* const component)
			template<class ...P>
			T* AddComponent(P&&... param)
			{
				assert(this->m_Components.size() < this->MAX_COMPONENTS && "Component limit exceeded!");
		
				T* component = nullptr;
		
				void* pComponentMem = this->m_ComponentAllocator->allocate(sizeof(T), alignof(T));
				if (pComponentMem != nullptr)
				{
					component = new (pComponentMem)T(std::forward<P>(param)...);
					this->m_Components.push_back(component);
				}
				else
				{
					LogError("Could not create new component (\'%s\')!", typeid(T).name());
				}
		
				return component;
			}
		
			// remove component from list
			inline void RemoveComponent(T* component)
			{
				this->m_Components.remove(component);
				this->m_ComponentAllocator->free((void*)component);
			}
		
			inline int GetComponentCount()
			{
				return this->m_Components.size();
			}
		
			// get component list
			inline TComponentList& const GetComponentList()
			{
				return this->m_Components;
			}

		}; // class ComponentContainer



		static const u64 MAX_T_COMPONENTS = ECS_MAX_T_COMPONENTS;

		using ComponentAllocator = Memory::Allocator::PoolAllocator;

		using ComponentContainerRegistry = std::unordered_map<ComponentTypeId, IComponentContainer*>;

		DECLARE_LOGGER

		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(ComponentManager&) = delete;

		ComponentContainerRegistry m_ComponentContainerRegistry;


		template<class T>
		inline ComponentContainer<T>* GetComponentContainer()
		{
			ComponentTypeId CID = T::STATIC_COMPONENT_TYPE_ID;

			auto it = this->m_ComponentContainerRegistry.find(CID);
			ComponentContainer<T>* cc = nullptr;

			if (it == this->m_ComponentContainerRegistry.end())
			{
				const size_t memSize = sizeof(T) * ComponentManager::MAX_T_COMPONENTS;

				ComponentAllocator* allocator = new ComponentAllocator(memSize, Allocate(memSize, "ComponentManager"), sizeof(T), alignof(T));

				cc = new ComponentContainer<T>(allocator, ComponentManager::MAX_T_COMPONENTS);
				this->m_ComponentContainerRegistry[CID] = cc;

				//LogDebug("New component container for \'%s\' created.", typeid(T).name()));
			}
			else
				cc = static_cast<ComponentContainer<T>*>(it->second);

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
		inline void RemoveComponent(T* component)
		{
			ComponentContainer<T>* cc = static_cast<ComponentContainer<T>*>(this->m_ComponentContainerRegistry[T::STATIC_COMPONENT_TYPE_ID]);
			if (cc != nullptr)
				cc->RemoveComponent(component);
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