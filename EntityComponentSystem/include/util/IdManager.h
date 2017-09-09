/*
	Author : Tobias Stein
	Date   : 17th July, 2016
	File   : IdManager.h
	
	Id manager class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __ID_MANAGER_H__
#define __ID_MANAGER_H__

#include "API.h"

namespace ECS { namespace util {

	using ObjectId	= u64;
	using TypeId	= u64;
	
	static const ObjectId	INVALID_OBJECT_ID	= -1;
	static const TypeId		INVALID_TYPE_ID		= -1;
	
	class ECS_API IdManager
	{
		static ObjectId s_NextValidId;
	
	protected:
	
		ObjectId m_Id;
	
		IdManager();
		~IdManager();
	
	public:
		
	
		inline const ObjectId GetId() const
		{
			return this->m_Id;
		}
	};

}} // namespace ECS::util

#endif // __ID_MANAGER_H__