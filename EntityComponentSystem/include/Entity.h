/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : Entity.h
	
	Enity class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __ENTITY_H__
#define __ENTITY_H__


#include "API.h"

#include "util/IdManager.h"

#include "ComponentManager.h"

namespace ECS {

	using EntityId = util::ObjectId;

	static const EntityId INVALID_ENTITY_ID = util::INVALID_OBJECT_ID;

	class ECS_API Entity
	{
	protected:

		DECLARE_STATIC_LOGGER

	private:

		static EntityId s_NextValidEntityId;

	protected:

		// set on create
		const EntityId				m_Id;

		// Compontent mask, sets a bit for any component type this entity owns
		std::vector<bool>			m_ComponentBitMask;

		// Component array
		std::vector<IComponent*>	m_Components;

		// if false, entity won't be updated
		bool						m_Active;

	public:

		Entity();
		virtual ~Entity();


		// ACCESSOR
		inline const EntityId GetEntityId() const
		{
			return this->m_Id;
		}

		// Component management: has, get, add, remove methods

		// Check if entity has component of type T. 
		template<class T>
		bool HasComponent() const
		{
			return this->m_ComponentBitMask[T::STATIC_COMPONENT_TYPE_ID];
		}

		template<class T>
		T* GetComponent() const
		{
			return HasComponent<T>() ? reinterpret_cast<T*>(this->m_Components[T::STATIC_COMPONENT_TYPE_ID]) : nullptr;
		}

		template<class T, class ...P>
		T* AddComponent(P&&... param)
		{
			if (HasComponent<T>())
			{
				assert(false && "Entiy already has component of this type.");
			}

			

			// Alloc and init component of type T
			//T* c = new T(std::forward<P>(param)...);

			// add component to corresponding system's list
			//ComponentManager<T>::GetInstance().AddComponent(c);
			//T* c = ComponentContainer<T>::GetInstance().AddComponent(std::forward<P>(param)...);
			T* c = ComponentManager::GetInstance().AddComponent<T>(std::forward<P>(param)...);


			// add component to entity's component array and set bit mask
			this->m_ComponentBitMask[T::STATIC_COMPONENT_TYPE_ID] = true;
			this->m_Components[T::STATIC_COMPONENT_TYPE_ID] = c;

			// set this entity as components owner
			c->m_Owner = this;

			return c;
		}

		template<class T>
		void RemoveComponent()
		{
			if (HasComponent<T>())
			{
				//// remove component to corresponding system's list
				//ComponentContainer<T>::GetInstance().RemoveComponent(this->m_Components[T::STATIC_COMPONENT_TYPE_ID]->As<T>());

				//// clear owner
				//this->m_Components[T::STATIC_COMPONENT_TYPE_ID]->m_Owner = nullptr;

				//// free component
				//delete this->m_Components[T::STATIC_COMPONENT_TYPE_ID];

				//// remove component from entity's component array and clear bit mask
				//this->m_ComponentBitMask[T::STATIC_COMPONENT_TYPE_ID] = false;
				//this->m_Components[T::STATIC_COMPONENT_TYPE_ID] = nullptr;
			}
		}

		// COMPARE ENTITIES

		inline bool operator==(const Entity& rhs) const
		{
			return this->m_Id == rhs.m_Id;
		}

		inline bool operator!=(const Entity& rhs) const
		{
			return this->m_Id != rhs.m_Id;
		}			


		// ACCESORS
		inline void SetActive(bool active)
		{
			this->m_Active = active;
		}

		inline bool IsActive() const
		{
			return this->m_Active;
		}
	};
}

#endif // __ENTITY_H__