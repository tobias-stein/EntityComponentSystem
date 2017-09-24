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
#include "IEntity.h"
#include "Memory/MemoryChunkAllocator.h"

namespace ECS
{
	template<class T>
	using EntityList = std::list<T*>;

	class ECS_API EntityManager
	{
		DECLARE_LOGGER


		class IEntityContainer
		{
		public:

			virtual ~IEntityContainer()
			{}

			virtual const char* GetEntityContainerTypeName() const = 0;

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

		}; // EntityContainer

		using EntityRegistry = std::unordered_map<EntityTypeId, IEntityContainer*>;

		EntityRegistry m_EntityRegistry;

	private:	

		friend class IEntity;

		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&) = delete;

		using EntityLookupTable = std::vector<void*>;


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
		/// Fn:	EntityId EntityManager::AqcuireEntityId();
		///
		/// Summary:	Returns an unused entity id.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	23/09/2017
		///
		/// Returns:	An EntityId.
		///-------------------------------------------------------------------------------------------------

		EntityId AqcuireEntityId();

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
		/// Fn:	template<class T> inline void* EntiyManager::CreateEntity()
		///
		/// Summary:	Creates a new entity. 
		/// DO NOT USE THAT METHOD DIRECTLY. ALWAYS USE Entity<T> class's new operator.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	11/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		///
		/// Returns:	Null if it fails, else the new entity.
		///-------------------------------------------------------------------------------------------------

		template<class T, class... ARGS>
		inline T* CreateEntity(ARGS&&... args)
		{		
			// aqcuire memory for new entity object of type T
			void* pObjectMemory = GetEntityContainer<T>()->CreateObject();

			// create entity inplace
			IEntity* entity = new (pObjectMemory)T(std::forward<ARGS>(args)...);

			// aqcuire unused entity id
			EntityId id = this->AqcuireEntityId();

			// set id
			entity->m_Id = id;

			return static_cast<T*>(entity);
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class T> inline void EntiyManager::DestroyEntity(void* entity)
		///
		/// Summary:	Destroies an entity.
		/// DO NOT USE THAT METHOD DIRECTLY. ALWAYS USE Entity<T> class's delete operator.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	11/09/2017
		///
		/// Typeparams:
		/// T - 	Generic type parameter.
		/// Parameters:
		/// entity - 	[in,out] If non-null, the entity.
		///-------------------------------------------------------------------------------------------------

		template<class T>
		inline void DestroyEntity(T* entity)
		{
			// free entity id
			this->ReleaseEntityId(entity->m_Id);

			// release object memory
			GetEntityContainer<T>()->DestroyObject(entity);
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

		inline void* GetEntity(const EntityId id) 
		{
			assert((id != INVALID_ENTITY_ID && id < this->m_EntityLUT.size()) && "Invalid entity id");
			return this->m_EntityLUT[id];
		}
	};
	 
} // namespace ECS

#endif // __ENTITY_MANAGER_H__