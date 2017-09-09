/*
	Author : Tobias Stein
	Date   : 9th July, 2016
	File   : EventHandler.cpp

	EventHandler class.

	All Rights Reserved. (c) Copyright 2016.
*/

#include "Event/EventHandler.h"

namespace ECS { namespace Event {

	Log::Logger* EventHandler::s_Logger = GetLogger("EventHandler");
	
	EventHandler::EventHandler()
	{
		s_Logger->LogInfo("Initialize EventHandler!");
	
		// allocate memory from global memory manager
		this->m_EventMemoryAllocator = new EventMemoryAllocator(EventHandler::EVENT_MEMORY_CAPACITY, Allocate(EventHandler::EVENT_MEMORY_CAPACITY, "EventHandler"));
	
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
		Free((void*)this->m_EventMemoryAllocator->GetFirstMemoryAddress());
	
		delete this->m_EventMemoryAllocator;
		this->m_EventMemoryAllocator = nullptr;
	
		s_Logger->LogInfo("Realse EventHandler!");
	}

}} // namespace ECS::Event