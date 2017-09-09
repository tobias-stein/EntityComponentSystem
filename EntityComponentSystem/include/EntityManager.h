/*
	Author : Tobias Stein
	Date   : 11th July, 2016
	File   : EntityManager.h
	
	Enity manager class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <unordered_map>


namespace ECS
{
	// forward declaration


	using EntityId = u64;

	static const EntityId INVALID_ENITYID = -1;


	class EntiyManager
	{
		//using EntityTypeMap = std::unordered_map<>
	};
	 
} // namespace ECS

#endif // __ENTITY_MANAGER_H__