/*
	Author : Tobias Stein
	Date   : 3rd July, 2016
	File   : Entity.h
	
	Enity class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __ENTITY_H__
#define __ENTITY_H__


#include "IEntity.h"

namespace ECS {

	///-------------------------------------------------------------------------------------------------
	/// Class:	Entity
	///
	/// Summary:	Base Entity class.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	11/09/2017
	///
	/// Typeparams:
	/// E - 	Type of the e.
	///-------------------------------------------------------------------------------------------------

	template<class E>
	class Entity : public IEntity
	{
		// Entity destruction always happens through EntityManager !!!
		void operator delete(void*) = delete;
		void operator delete[](void*) = delete;

	public:

		static const EntityTypeId STATIC_ENTITY_TYPE_ID;

	public:

		Entity()
		{}

		virtual ~Entity()
		{}

		static const EntityTypeId GetStaticEntityTypeId()
		{
			return STATIC_ENTITY_TYPE_ID;
		}
	};

	template<class T>
	const EntityTypeId Entity<T>::STATIC_ENTITY_TYPE_ID = util::Internal::FamilyTypeCounter<IEntity>::Increment();
}

#endif // __ENTITY_H__