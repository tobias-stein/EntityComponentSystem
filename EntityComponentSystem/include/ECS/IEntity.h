///-------------------------------------------------------------------------------------------------
/// File:	include\IEntity.h.
///
/// Summary:	Base entity class containing no morte than entity id and state falgs.
///-------------------------------------------------------------------------------------------------

#ifndef __I_ENTITY_H__
#define __I_ENTITY_H__

#pragma once

#include "API.h"
#include "util/Handle.h"

namespace ECS
{
	using EntityTypeId						= TypeID;

	using EntityId							= util::Handle64;

	static const EntityId INVALID_ENTITY_ID = util::Handle64::INVALID_HANDLE;

	class ECS_API IEntity
	{
		friend class EntityManager;

	private:

		// set on create; in EntityManager
		ComponentManager*	m_ComponentManagerInstance;

	protected:

		DECLARE_STATIC_LOGGER

		

		// set on create; in EntityManager
		EntityId				m_EntityID;		

		// if false, entity won't be updated
		bool					m_Active;

	public:

		IEntity();
		virtual ~IEntity();

		template<class T>
		T* GetComponent() const
		{
			return this->m_ComponentManagerInstance->GetComponent<T>(this->m_EntityID);
		}

		template<class T, class ...P>
		T* AddComponent(P&&... param)
		{
			return this->m_ComponentManagerInstance->AddComponent<T>(this->m_EntityID, std::forward<P>(param)...);
		}

		template<class T>
		void RemoveComponent()
		{
			this->m_ComponentManagerInstance->RemoveComponent<T>(this->m_EntityID);
		}

		// COMPARE ENTITIES

		inline bool operator==(const IEntity& rhs) const { return this->m_EntityID == rhs.m_EntityID; }
		inline bool operator!=(const IEntity& rhs) const { return this->m_EntityID != rhs.m_EntityID; }
		inline bool operator==(const IEntity* rhs) const { return this->m_EntityID == rhs->m_EntityID; }
		inline bool operator!=(const IEntity* rhs) const { return this->m_EntityID != rhs->m_EntityID; }

		// ACCESORS
		virtual const EntityTypeId GetStaticEntityTypeID() const = 0;
		
		inline const EntityId GetEntityID() const { return this->m_EntityID; }
		
		void SetActive(bool active);

		inline bool IsActive() const { return this->m_Active; }

		virtual void OnEnable() {}
		virtual void OnDisable() {}
	};	

} // namespace ECS

#endif // __I_ENTITY_H__