///-------------------------------------------------------------------------------------------------
/// File:	include\IEntity.h.
///
/// Summary:	Base entity class containing no morte than entity id and state falgs.
///-------------------------------------------------------------------------------------------------

#ifndef __I_ENTITY_H__
#define __I_ENTITY_H__

#pragma once

#include "API.h"

#include "util/IdManager.h"

namespace ECS
{
	using EntityTypeId	= util::TypeId;

	using EntityId		= util::ObjectId;

	static const EntityId INVALID_ENTITY_ID = util::INVALID_OBJECT_ID;

	class ECS_API IEntity
	{
		friend class EntityManager;

	protected:

		DECLARE_STATIC_LOGGER

		// set on create
		EntityId				m_EntityID;		

		// if false, entity won't be updated
		bool					m_Active;

	public:

		IEntity();
		virtual ~IEntity();

		template<class T>
		T* GetComponent()
		{
			return ECS_Engine->ECS_ComponentManager->GetComponent<T>(this->m_EntityID);
		}

		template<class T, class ...P>
		T* AddComponent(P&&... param)
		{
			return ECS_Engine->ECS_ComponentManager->AddComponent<T>(this->m_EntityID, std::forward<P>(param)...);
		}

		template<class T>
		void RemoveComponent()
		{
			ECS_Engine->ECS_ComponentManager->RemoveComponent<T>(this->m_EntityID);
		}

		// COMPARE ENTITIES

		inline bool operator==(const IEntity& rhs) const { return this->m_EntityID == rhs.m_EntityID; }
		inline bool operator!=(const IEntity& rhs) const { return this->m_EntityID != rhs.m_EntityID; }


		// ACCESORS
		virtual const EntityTypeId GetStaticEntityTypeID() const = 0;
		
		inline const EntityId GetEntityID() const { return this->m_EntityID; }
		
		inline void SetActive(bool active) { this->m_Active = active; }
		inline bool IsActive() const { return this->m_Active; }
	};

} // namespace ECS

#endif // __I_ENTITY_H__