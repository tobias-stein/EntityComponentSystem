/*
Author : Tobias Stein
Date   : 7th September, 2017
File   : ComponentManager.h

Manages all component container.

All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__


#include "API.h"

#include "Memory/MemoryChunkAllocator.h"

#include "Component.h"


namespace ECS
{
	class ECS_API ComponentManager : Memory::GlobalMemoryUser
	{
		DECLARE_LOGGER
		
		

		class IComponentContainer
		{
		public:
		
			virtual ~IComponentContainer()
			{}

			virtual const char* GetComponentContainerTypeName() const = 0;
		};
		
		template<class T>
		class ComponentContainer : public Memory::MemoryChunkAllocator<T, COMPONENT_T_CHUNK_SIZE>, public IComponentContainer
		{
			ComponentContainer(const ComponentContainer&) = delete;
			ComponentContainer& operator=(ComponentContainer&) = delete;
		

		public:
		
			ComponentContainer() : MemoryChunkAllocator("ComponentManager")
			{}

			virtual ~ComponentContainer()
			{}

			virtual const char* GetComponentContainerTypeName() const override
			{
				return typeid(T).name();
			}		

		}; // class ComponentContainer



		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator=(ComponentManager&) = delete;

		using ComponentContainerRegistry = std::unordered_map<ComponentTypeId, IComponentContainer*>;

		ComponentContainerRegistry m_ComponentContainerRegistry;


		template<class T>
		inline ComponentContainer<T>* GetComponentContainer()
		{
			ComponentTypeId CID = T::STATIC_COMPONENT_TYPE_ID;

			auto it = this->m_ComponentContainerRegistry.find(CID);
			ComponentContainer<T>* cc = nullptr;

			if (it == this->m_ComponentContainerRegistry.end())
			{
				cc = new ComponentContainer<T>();
				this->m_ComponentContainerRegistry[CID] = cc;
			}
			else
				cc = static_cast<ComponentContainer<T>*>(it->second);

			assert(cc != nullptr && "Failed to create ComponentContainer<T>!");
			return cc;
		}


	public:
		
		template<class T>
		using TComponentIterator = typename ComponentContainer<T>::iterator;

		ComponentManager();
		~ComponentManager();

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T, class ...ARGS> inline T* ComponentManager::AddComponent(ARGS&&... args)
		///
		/// Summary:	Creates a new component with provided parameters.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// T - 	   	Generic type parameter.
		/// ...ARGS -  	Type of the ...args.
		/// Parameters:
		/// args - 	Variable arguments providing [in,out] The arguments.
		///
		/// Returns:	Null if it fails, else a pointer to a T.
		///-------------------------------------------------------------------------------------------------

		template<class T, class ...ARGS>
		inline T* AddComponent(ARGS&&... args)
		{
			// aqcuire memory for new component object of type T
			void* pObjectMemory = GetComponentContainer<T>()->CreateObject();

			// create component inplace
			void* component = new (pObjectMemory)T(std::forward<ARGS>(args)...);

			return static_cast<T*>(component);
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T> inline void ComponentManager::RemoveComponent(T* component)
		///
		/// Summary:	Removes the component described by component.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		/// Parameters:
		/// component - 	[in,out] If non-null, the component.
		///-------------------------------------------------------------------------------------------------

		template<class T>
		inline void RemoveComponent(T* component)
		{
			// release object memory
			GetComponentContainer<T>()->DestroyObject(component);
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T> inline TComponentIterator<T> ComponentManager::begin()
		///
		/// Summary:	Returns an forward iterator object that points to the beginning of a collection of 
		/// all components of type T.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		///
		/// Returns:	A TComponentIterator&lt;T&gt;
		///-------------------------------------------------------------------------------------------------

		template<class T>
		inline TComponentIterator<T> begin()
		{
			return GetComponentContainer<T>()->begin();
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T> inline TComponentIterator<T> ComponentManager::end()
		///
		/// Summary:	Returns an forward iterator object that points to the end of a collection of
		/// all components of type T.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		///
		/// Returns:	A TComponentIterator&lt;T&gt;
		///-------------------------------------------------------------------------------------------------

		template<class T>
		inline TComponentIterator<T> end()
		{
			return GetComponentContainer<T>()->end();
		}

	}; // ComponentManager


} // namespace ECS

#endif // __COMPONENT_MANAGER_H__