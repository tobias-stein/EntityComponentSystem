/*
	Author : Tobias Stein
	Date   : 9th July, 2016
	File   : EventHandler.cpp

	EventHandler class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Event/EventHandler.h"

namespace ECS { namespace Event {	

	EventHandler::EventHandler()
	{
		DEFINE_LOGGER("EventHandler")
		LogInfo("Initialize EventHandler!");
	
		// allocate memory from global memory manager
		this->m_EventMemoryAllocator = new EventMemoryAllocator(ECS_EVENT_MEMORY_BUFFER_SIZE, Allocate(ECS_EVENT_MEMORY_BUFFER_SIZE, "EventHandler"));
	
		this->m_EventStorage.reserve(1024);
	}
	
	EventHandler::~EventHandler()
	{
		for (EventHandler::EventDispatcherMap::iterator it = this->m_EventDispatcherMap.begin(); it != this->m_EventDispatcherMap.end(); ++it)
		{
			delete (*it).second;
			(*it).second = nullptr;
		}
	
		this->m_EventDispatcherMap.clear();
	
		// Release allocated memory
		Free((void*)this->m_EventMemoryAllocator->GetMemoryAddress0());
	
		delete this->m_EventMemoryAllocator;
		this->m_EventMemoryAllocator = nullptr;
	
		LogInfo("Relealse EventHandler!");
	}

}} // namespace ECS::Event