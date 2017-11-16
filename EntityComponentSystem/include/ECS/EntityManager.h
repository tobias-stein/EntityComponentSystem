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

#include "Memory/MemoryChunkAllocator.h"

#include "util/Handle.h"

#pragma warning(push)

// warning C4291: 'void *operator new(::size_t,void *) throw()': no matching operator delete found; memory will not be freed if initialization throws an exception
// note we are using custom memory allocator no need for delete
#pragma warning(disable: 4291)

namespace ECS
{	
	using EntityHandleTable = util::HandleTable<IEntity, EntityId>;


	class ECS_API EntityManager
	{
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
				static const char* ENTITY_TYPE_NAME{ typeid(T).name() };
				return ENTITY_TYPE_NAME;
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

		using PendingDestroyedEntities = std::vector<EntityId>;
		PendingDestroyedEntities m_PendingDestroyedEntities;
		size_t m_NumPendingDestroyedEntities;

		/// Summary:	The component manager instance.
		ComponentManager*	m_ComponentManagerInstance;

	private:	

		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&) = delete;

		EntityHandleTable m_EntityHandleTable;



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

		EntityManager(ComponentManager* componentManagerInstance);
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

			ECS::EntityId entityId = this->AqcuireEntityId((T*)pObjectMemory);

			((T*)pObjectMemory)->m_EntityID = entityId;
			((T*)pObjectMemory)->m_ComponentManagerInstance = this->m_ComponentManagerInstance;

			// create entity inplace
			IEntity* entity = new (pObjectMemory)T(std::forward<ARGS>(args)...);	

			return entityId;
		}


		void DestroyEntity(EntityId entityId)
		{
			IEntity* entity = this->m_EntityHandleTable[entityId];
		
			const EntityTypeId ETID = entity->GetStaticEntityTypeID();

			if (this->m_NumPendingDestroyedEntities < this->m_PendingDestroyedEntities.size())
			{
				this->m_PendingDestroyedEntities[this->m_NumPendingDestroyedEntities++] = entityId;
			}
			else
			{
				this->m_PendingDestroyedEntities.push_back(entityId);
				this->m_NumPendingDestroyedEntities++;
			}
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

		inline IEntity* GetEntity(EntityId entityId)
		{
			return this->m_EntityHandleTable[entityId];
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	inline EntityId EntityManager::GetEntityId(EntityId::index_type index)
		///
		/// Summary:	Gets the currently stored entity identifier at the given index.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	2/10/2017
		///
		/// Parameters:
		/// index - 	Zero-based index of the.
		///
		/// Returns:	The entity identifier.
		///-------------------------------------------------------------------------------------------------

		inline EntityId GetEntityId(EntityId::value_type index) const
		{
			return this->m_EntityHandleTable[index];
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void EntityManager::RemoveDestroyedEntities();
		///
		/// Summary:	Removes all destroyed entities.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	8/10/2017
		///-------------------------------------------------------------------------------------------------

		void RemoveDestroyedEntities();
	};

	 
} // namespace ECS

#pragma warning(pop)

#endif // __ENTITY_MANAGER_H__