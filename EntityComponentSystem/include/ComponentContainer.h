/*
	Author : Tobias Stein
	Date   : 4th July, 2016
	File   : ComponentContainer.h

	Manager class for specific component types

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __COMPONENT_CONTAINER_H__
#define __COMPONENT_CONTAINER_H__



#include "Memory/Allocator/PoolAllocator.h"

#include "Component.h"


namespace ECS { 
	
	//template<class T>
	//using ComponentList = std::list<T*>;
	//
	//namespace Internal {

	//
	//class IComponentContainer 
	//{
	//public:

	//	virtual ~IComponentContainer()
	//	{}
	//};

	//template<class T>
	//class ComponentContainer : public IComponentContainer
	//{
	//private:

	//	using ComponentAllocator = Memory::Allocator::PoolAllocator;

	//	using TComponentList = ComponentList<T>;

	//	const size_t MAX_COMPONENTS;

	//	DECLARE_STATIC_LOGGER

	//	ComponentAllocator* m_ComponentAllocator;

	//	TComponentList m_Components;

	//	ComponentContainer(const ComponentContainer&) = delete;
	//	ComponentContainer& operator=(ComponentContainer&) = delete;

	//public:

	//	ComponentContainer(ComponentAllocator* allocator, const size_t maxComponents) : 
	//		m_ComponentAllocator(allocator),
	//		MAX_COMPONENTS(maxComponents)
	//	{
	//	}

	//	~ComponentContainer()
	//	{
	//		LogInfo("Destroy \'%s\' components ...", typeid(T).name());

	//		for (auto component : this->m_Components)
	//		{
	//			((IComponent*)component)->~IComponent();
	//			component = nullptr;
	//		}

	//		this->m_Components.clear();
	//	}


	//	// Add component to listinline void AddComponent(T* const component)
	//	template<class ...P>
	//	T* AddComponent(P&&... param)
	//	{
	//		assert(this->m_Components.size() < this->MAX_COMPONENTS && "Component limit exceeded!");

	//		T* component = nullptr;

	//		void* pComponentMem = this->m_ComponentAllocator->allocate(sizeof(T), alignof(T));
	//		if (pComponentMem != nullptr)
	//		{
	//			component = new (pComponentMem)T(std::forward<P>(param)...);
	//			this->m_Components.push_back(component);
	//		}
	//		else
	//		{
	//			LogError("Could not create new component (\'%s\')!", typeid(T).name());
	//		}
	//		
	//		return component;
	//	}

	//	// remove component from list
	//	inline void RemoveComponent(T* const component)
	//	{
	//		this->m_Components.remove(component);
	//	}

	//	inline int GetComponentCount()
	//	{
	//		return this->m_Components.size();
	//	}

	//	// get component list
	//	inline TComponentList& const GetComponentList()
	//	{
	//		return this->m_Components;
	//	}
	//}; // class ComponentContainer

	//DEFINE_STATIC_LOGGER_TEMPLATE(ComponentContainer, T, "ComponentManager")

}} // namespace ECS::Internal

#endif // __COMPONENT_CONTIANER_H__