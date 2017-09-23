///-------------------------------------------------------------------------------------------------
/// File:	include\IEntity.h.
///
/// Summary:	Declares the IEntity interface.
///-------------------------------------------------------------------------------------------------

#ifndef __I_ENTITY_H__
#define __I_ENTITY_H__

#pragma once

#include "API.h"

#include "util/IdManager.h"

#include "ComponentManager.h"

namespace ECS
{
	using EntityTypeId	= util::TypeId;

	using EntityId = util::ObjectId;

	static const EntityId INVALID_ENTITY_ID = util::INVALID_OBJECT_ID;


	class ECS_API IEntity
	{
	private:

		// set on create
		EntityId					m_Id;

		friend class EntityManager;

	protected:

		DECLARE_STATIC_LOGGER

		// Compontent mask, sets a bit for any component type this entity owns
		std::vector<bool>			m_ComponentBitMask;

		// Component array
		std::vector<IComponent*>	m_Components;

		// if false, entity won't be updated
		bool						m_Active;

	public:

		IEntity();
		virtual ~IEntity();

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

			// add component
			T* c = ECS_Engine->ECS_ComponentManager->AddComponent<T>(std::forward<P>(param)...);


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
				// remove component
				ECS_Engine->ECS_ComponentManager->RemoveComponent<T>(this->m_Components[T::STATIC_COMPONENT_TYPE_ID]->As<T>());

				// remove component from entity's component array and clear bit mask
				this->m_ComponentBitMask[T::STATIC_COMPONENT_TYPE_ID] = false;
				this->m_Components[T::STATIC_COMPONENT_TYPE_ID] = nullptr;
			}
		}

		// COMPARE ENTITIES

		inline bool operator==(const IEntity& rhs) const
		{
			return this->m_Id == rhs.m_Id;
		}

		inline bool operator!=(const IEntity& rhs) const
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

} // namespace ECS

#endif // __I_ENTITY_H__