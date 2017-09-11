///-------------------------------------------------------------------------------------------------
/// File:	include\API.h.
///
/// Summary:	API.
/// 

/*
Preprocessor defines:

	ECS_DISABLE_LOGGING			- Disable logging feature.



*/

#ifndef __ECS_API_H__
#define __ECS_API_H__
#pragma once


#define ENITY_ALLOCATION_AMOUNT 512


#include "Platform.h"

#include "Log/Logger.h"



namespace ECS 
{
	namespace Log {

		namespace Internal
		{

			class LoggerManager;
		}
	}

	namespace Memory
	{
		namespace Internal
		{
			class MemoryManager;
		}
	}

	namespace Event
	{
		class EventHandler;
	}


	class EntityManager;
	class SystemManager;
	class ComponentManager;



	extern Log::Internal::LoggerManager*		ECSLoggerManager;

	extern Memory::Internal::MemoryManager*		ECSMemoryManager;

	ECS_API extern EntityManager*				ECSEntityManager;

	ECS_API extern ComponentManager*			ECSComponentManager;

	ECS_API extern SystemManager*				ECSSystemManager;

	ECS_API extern Event::EventHandler*			ECSEventHandler;



	///-------------------------------------------------------------------------------------------------
	/// Fn:	ECS_API void Terminate();
	///
	/// Summary:	Terminates this ECS framework.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	11/09/2017
	///-------------------------------------------------------------------------------------------------

	ECS_API void Terminate();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	Log::Logger* ECS_API GetLogger(const char* logger);
	///
	/// Summary:	Returns a logger instance. Caller must not delete this instance this will be handled
	/// by intern logger manager.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	9/09/2017
	///
	/// Parameters:
	/// logger - 	The logger name.
	///
	/// Returns:	The logger.
#if !ECS_DISABLE_LOGGING
	ECS_API Log::Logger* GetLogger(const char* logger);
#endif


	namespace Memory
	{
		///-------------------------------------------------------------------------------------------------
		/// Class:	GlobalMemoryUser
		///
		/// Summary:	Any class that wants to use the global memory must derive from this class.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	9/09/2017
		///-------------------------------------------------------------------------------------------------

		class ECS_API GlobalMemoryUser
		{
		private:

			Internal::MemoryManager* ECS_MEMORY_MANAGER;

		public:

			GlobalMemoryUser();
			virtual ~GlobalMemoryUser();

			inline const void* Allocate(size_t memSize, const char* user = nullptr);
			inline void Free(void* pMem);
		};

	} // namespace ECS::Memory

} // namespace ECS

#endif // __ECS_API_H__