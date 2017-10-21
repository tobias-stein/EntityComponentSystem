///-------------------------------------------------------------------------------------------------
/// File:	include\Memory\MemoryChunkAllocator.h.
///
/// Summary:	Auxilary allocator class using base PoolAllocator. This allocator dynamically 
/// creates memory chunks when out of capacity. Each memory chunk is managed by a single PoolAllocator.
///-------------------------------------------------------------------------------------------------

#ifndef __MEMORY_CHUNK_ALLOCATOR_H__
#define __MEMORY_CHUNK_ALLOCATOR_H__

#include "API.h"
#include "Memory/Allocator/PoolAllocator.h"


namespace ECS { namespace Memory {

	template<class  OBJECT_TYPE, size_t MAX_CHUNK_OBJECTS>
	class MemoryChunkAllocator : protected Memory::GlobalMemoryUser
	{
		static const size_t MAX_OBJECTS = typename MAX_CHUNK_OBJECTS;

		/// Summary:	Byte size to fit approx. MAX_CHUNK_OBJECTS objects.
		static const size_t ALLOC_SIZE = (sizeof(OBJECT_TYPE) + alignof(OBJECT_TYPE)) * MAX_OBJECTS;

		const char* m_AllocatorTag;

	public:

		using Allocator  = Memory::Allocator::PoolAllocator;
		using ObjectList = std::list<OBJECT_TYPE*>;

		

		///-------------------------------------------------------------------------------------------------
		/// class:	MemoryChunk
		///
		/// Summary:	Helper struct to capsule an allocator and object list. The object list is used to keep
		/// track of objects start addresses in memory managed by the allocator.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///-------------------------------------------------------------------------------------------------

		class MemoryChunk
		{
		public:

			Allocator*		allocator;
			ObjectList		objects;

			uptr			chunkStart;
			uptr			chunkEnd;

			MemoryChunk(Allocator* allocaor) :
				allocator(allocaor)
			{
				this->chunkStart = reinterpret_cast<uptr>(allocator->GetMemoryAddress0());
				this->chunkEnd = this->chunkStart + ALLOC_SIZE;
				this->objects.clear();
			}

		}; // class EntityMemoryChunk

		using MemoryChunks = std::list<MemoryChunk*>;

		///-------------------------------------------------------------------------------------------------
		/// Class:	iterator
		///
		/// Summary:	An iterator for linear search actions in allocated memory chungs.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///-------------------------------------------------------------------------------------------------

		class iterator : public std::iterator<std::forward_iterator_tag, OBJECT_TYPE>
		{
			typename MemoryChunks::iterator	m_CurrentChunk;
			typename MemoryChunks::iterator	m_End;

			typename ObjectList::iterator	m_CurrentObject;


			public:

				iterator(typename MemoryChunks::iterator begin, typename MemoryChunks::iterator end) :
					m_CurrentChunk(begin),
					m_End(end)
				{				
					if (begin != end)
					{	
						assert((*m_CurrentChunk) != nullptr);
						m_CurrentObject = (*m_CurrentChunk)->objects.begin();
					}
					else
					{
						m_CurrentObject = (*std::prev(m_End))->objects.end();
					}
				}
				

				inline iterator& operator++()
				{
					// move to next object in current chunk
					m_CurrentObject++;

					// if we reached end of list, move to next chunk
					if (m_CurrentObject == (*m_CurrentChunk)->objects.end())
					{
						m_CurrentChunk++;

						if (m_CurrentChunk != m_End)
						{
							// set object iterator to begin of next chunk list
							assert((*m_CurrentChunk) != nullptr);
							m_CurrentObject = (*m_CurrentChunk)->objects.begin();
						}
					}

					return *this;
				}

				inline OBJECT_TYPE& operator*() const { return *m_CurrentObject; }
				inline OBJECT_TYPE* operator->() const { return *m_CurrentObject; }

				inline bool operator==(iterator& other) { return ((this->m_CurrentChunk == other.m_CurrentChunk) && (this->m_CurrentObject == other.m_CurrentObject));
				}
				inline bool operator!=(iterator& other) 
				{ 
					return ((this->m_CurrentChunk != other.m_CurrentChunk) && (this->m_CurrentObject != other.m_CurrentObject));
				}

		}; // ComponentContainer::iterator

	protected:

		MemoryChunks m_Chunks;

	public:


		MemoryChunkAllocator(const char* allocatorTag = nullptr) :
			m_AllocatorTag(allocatorTag)
		{
			

			// create initial chunk
			Allocator* allocator = new Allocator(ALLOC_SIZE, Allocate(ALLOC_SIZE, allocatorTag), sizeof(OBJECT_TYPE), alignof(OBJECT_TYPE));
			this->m_Chunks.push_back(new MemoryChunk(allocator));
		}

		virtual ~MemoryChunkAllocator()
		{
			// make sure all entities will be released!
			for (auto chunk : this->m_Chunks)
			{
				for (auto obj : chunk->objects)
					((OBJECT_TYPE*)obj)->~OBJECT_TYPE();
		
				chunk->objects.clear();

				// free allocated allocator memory
				Free((void*)chunk->allocator->GetMemoryAddress0());
				delete chunk->allocator;
				chunk->allocator = nullptr;

				// delete helper chunk object
				delete chunk;
				chunk = nullptr;
			}
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	inline void* MemoryChunkAllocator::CreateObject()
		///
		/// Summary:	Creates the object.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Returns:	Null if it fails, else the new object.
		///-------------------------------------------------------------------------------------------------

		void* CreateObject()
		{
			void* slot = nullptr;

			// get next free slot
			for (auto chunk : this->m_Chunks)
			{
				if (chunk->objects.size() > MAX_OBJECTS)
					continue;

				slot = chunk->allocator->allocate(sizeof(OBJECT_TYPE), alignof(OBJECT_TYPE));
				if (slot != nullptr)
				{
					chunk->objects.push_back((OBJECT_TYPE*)slot);
					break;
				}
			}

			// all chunks are full... allocate a new one
			if (slot == nullptr)
			{
				Allocator* allocator = new Allocator(ALLOC_SIZE, Allocate(ALLOC_SIZE, this->m_AllocatorTag), sizeof(OBJECT_TYPE), alignof(OBJECT_TYPE));
				MemoryChunk* newChunk = new MemoryChunk(allocator);		

				// put new chunk in front
				this->m_Chunks.push_front(newChunk);

				slot = newChunk->allocator->allocate(sizeof(OBJECT_TYPE), alignof(OBJECT_TYPE));

				assert(slot != nullptr && "Unable to create new object. Out of memory?!");
				newChunk->objects.clear();
				newChunk->objects.push_back((OBJECT_TYPE*)slot);
			}

			return slot;
		}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	inline void MemoryChunkAllocator::DestroyObject(void* object)
		///
		/// Summary:	Destroys the object.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	24/09/2017
		///
		/// Parameters:
		/// object - 	[in,out] If non-null, the object.
		///-------------------------------------------------------------------------------------------------

		void DestroyObject(void* object)
		{
			uptr adr = reinterpret_cast<uptr>(object);

			for (auto chunk : this->m_Chunks)
			{
				if (chunk->chunkStart <= adr && adr < chunk->chunkEnd)
				{
					// note: no need to call d'tor since it was called already by 'delete'

					chunk->objects.remove((OBJECT_TYPE*)object);
					chunk->allocator->free(object);
					return;
				}
			}

			assert(false && "Failed to delete object. Memory corruption?!");
		}


		inline iterator begin() { return iterator(this->m_Chunks.begin(), this->m_Chunks.end()); }
		inline iterator end() { return iterator(this->m_Chunks.end(), this->m_Chunks.end()); }

	}; // MemoryChunkAllocator 

}} // namespace ECS::Memory

#endif // __MEMORY_CHUNK_ALLOCATOR_H__

