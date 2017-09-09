/*
	Author : Tobias Stein
	Date   : 17th July, 2016
	File   : IdManager.cpp

	Id manager class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "util/IdManager.h"

namespace ECS { namespace util {

	ObjectId IdManager::s_NextValidId{ 0u };
	
	IdManager::IdManager() :
		m_Id(s_NextValidId++)
	{}
	
	IdManager::~IdManager()
	{}

}} // namespace ECS::util