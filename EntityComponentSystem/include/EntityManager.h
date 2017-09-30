/*
	Author : Tobias Stein
	Date   : 11th July, 2016
	File   : EntityManager.h
	
	Enity manager class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "API.h"
#include "Engine.h"

#include "IEntity.h"
#include "ComponentManager.h"

#include "Event/Event.h"
#include "Event/EventHandler.h"

#include "Memory/MemoryChunkAllocator.h"



namespace ECS
{
	///-------------------------------------------------------------------------------------------------
	/// Struct:	ECS_API
	///
	/// Summary:	Sent when new entity object was created.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	30/09/2017
	///-------------------------------------------------------------------------------------------------

	struct EntityCreated : public Event::Event<EntityCreated>
	{
		EntityId		m_EntityID;
		EntityTypeId	m_EntityTypeID;

		EntityCreated(EntityId entityId, EntityTypeId entityTypeId) :
			m_EntityID(entityId),
			m_EntityTypeID(entityTypeId)
		{}

	}; // struct EntityCreated 

	   ///-------------------------------------------------------------------------------------------------
	   /// Struct:	ECS_API
	   ///
	   /// Summary:	Sent when entity object was destroyed.
	   ///
	   /// Author:	Tobias Stein
	   ///
	   /// Date:	30/09/2017
	   ///-------------------------------------------------------------------------------------------------

	struct EntityDestroyed : public Event::Event<EntityDestroyed>
	{
		EntityId		m_EntityID;
		EntityTypeId	m_EntityTypeID;

		EntityDestroyed(EntityId entityId, EntityTypeId entityTypeId) :
			m_EntityID(entityId),
			m_EntityTypeID(entityTypeId)
		{}

	}; // struct EntityDestroyed


	template<class T>
	using EntityList = std::list<T*>;

	class ECS_API EntityManager
	{
		friend class IEntity;

		DECLARE_LOGGER


		class IEntityContainer
		{
		public:

			virtual ~IEntityContainer()
			{}

			virtual const char* GetEntityContainerTypeName() const = 0;

			virtual void DestroyEntity(IEntity* object) = 0;

		}; // class IEntityContainer

		///-------------------------------------------------------------------------------------------------
		/// Class:	EntityContainer
		///
		/// Summary:	An entity container that manages memory chunks of enities T.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	23/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		///-------------------------------------------------------------------------------------------------

		template<class T>
		class EntityContainer : public Memory::MemoryChunkAllocator<T, ENITY_T_CHUNK_SIZE>, public IEntityContainer
		{

			EntityContainer(const EntityContainer&) = delete;
			EntityContainer& operator=(EntityContainer&) = delete;

		public:

			EntityContainer() : MemoryChunkAllocator("EntityManager")
			{}

			virtual ~EntityContainer()
			{}

			virtual const char* GetEntityContainerTypeName() const override
			{ 
				return typeid(T).name();
			}

			virtual void DestroyEntity(IEntity* object) override
			{
				// call d'tor
				object->~IEntity();

				this->DestroyObject(object);
			}

		}; // EntityContainer

		using EntityRegistry = std::unordered_map<EntityTypeId, IEntityContainer*>;

		EntityRegistry m_EntityRegistry;

	private:	

		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&) = delete;

		using EntityLookupTable = std::vector<IEntity*>;


		/// Summary:	Maps an entity id to object.
		EntityLookupTable m_EntityLUT;

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T> inline EntityContainer<T>* EntityManager::GetEntityContainer()
		///
		/// Summary:	Returns/Creates an entity container for entities of type T.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	23/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		///
		/// Returns:	Null if it fails, else the entity container.
		///-------------------------------------------------------------------------------------------------

		template<class T>
		inline EntityContainer<T>* GetEntityContainer()
		{
			EntityTypeId EID = T::STATIC_ENTITY_TYPE_ID;

			auto it = this->m_EntityRegistry.find(EID);
			EntityContainer<T>* ec = nullptr;
						
			if (it == this->m_EntityRegistry.end())
			{
				ec = new EntityContainer<T>();
				this->m_EntityRegistry[EID] = ec;
			}
			else
				ec = (EntityContainer<T>*)it->second;

			assert(ec != nullptr && "Failed to create EntityContainer<T>!");
			return ec;
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	EntityId EntityManager::AqcuireEntityId(IEntity* entity);
		///
		/// Summary:	Aqcuire entity identifier. This method will be used be IEntity class c'tor to set
		/// the entity id on creation.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Parameters:
		/// entity - 	[in,out] If non-null, the entity.
		///
		/// Returns:	An EntityId.
		///-------------------------------------------------------------------------------------------------

		EntityId AqcuireEntityId(IEntity* entity);

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void EntityManager::ReleaseEntityId(EntityId id);
		///
		/// Summary:	Releases the entity identifier for reuse.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	23/09/2017
		///
		/// Parameters:
		/// id - 	The identifier.
		///-------------------------------------------------------------------------------------------------

		void ReleaseEntityId(EntityId id);

	public:

		EntityManager();
		~EntityManager();

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T, class... ARGS> EntityId EntityManager::CreateEntity(ARGS&&... args)
		///
		/// Summary:	Creates an entity of type T and returns its id.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	30/09/2017
		///
		/// Typeparams:
		/// T - 	   	Generic type parameter.
		/// ARGS - 	   	Type of the arguments.
		/// Parameters:
		/// args - 	Variable arguments providing [in,out] The arguments.
		///
		/// Returns:	The new entity.
		///-------------------------------------------------------------------------------------------------

		template<class T, class... ARGS>
		EntityId CreateEntity(ARGS&&... args)
		{		
			// aqcuire memory for new entity object of type T
			void* pObjectMemory = GetEntityContainer<T>()->CreateObject();

			// create entity inplace
			IEntity* entity = new (pObjectMemory)T(std::forward<ARGS>(args)...);	

			// Broadcast CreateEntity event
			ECS_Engine->ECS_EventHandler->Send<EntityCreated>(entity->GetEntityID(), entity->GetStaticEntityTypeID());

			return entity->GetEntityID();
		}


		void DestroyEntity(EntityId entityId)
		{
			assert(entityId < this->m_EntityLUT.size() && "Trying to destroy an entity with an invalid entity id!");

			IEntity* entity = this->m_EntityLUT[entityId];

			const EntityTypeId ETID = entity->GetStaticEntityTypeID();

			// get appropriate entity container and destroy entity
			auto it = this->m_EntityRegistry.find(ETID);
			if (it != this->m_EntityRegistry.end())
			{
				it->second->DestroyEntity(entity);
			}

			// Broadcast EntityDestroyed event
			ECS_Engine->ECS_EventHandler->Send<EntityDestroyed>(entityId, ETID);

			// release entity's components as well
			ECS_Engine->ECS_ComponentManager->RemoveAllComponents(entityId);
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	inline void* EntityManager::GetEntity(const EntityId id)
		///
		/// Summary:	Get an entity object by its id.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	23/09/2017
		///
		/// Parameters:
		/// id - 	The identifier.
		///
		/// Returns:	Null if it fails, else the entity.
		///-------------------------------------------------------------------------------------------------

		inline IEntity* GetEntity(const EntityId id)
		{
			assert((id != INVALID_ENTITY_ID && id < this->m_EntityLUT.size()) && "Invalid entity id");
			return this->m_EntityLUT[id];
		}
	};
	 
} // namespace ECS

#endif // __ENTITY_MANAGER_H__