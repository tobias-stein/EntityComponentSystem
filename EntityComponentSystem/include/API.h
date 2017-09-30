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

#define ENITY_LUT_GROW				1024

#define ENITY_T_CHUNK_SIZE			512

#define COMPONENT_LUT_GROW			1024

#define COMPONENT_T_CHUNK_SIZE		512


#include "Platform.h"

#include "Log/Logger.h"

namespace ECS 
{
	namespace Log {

		namespace Internal
		{
#if !ECS_DISABLE_LOGGING

			class  LoggerManager;
			extern LoggerManager*				ECSLoggerManager;

			///-------------------------------------------------------------------------------------------------
			/// Fn:	ECS_API Log::Logger* GetLogger(const char* logger);
			///
			/// Summary:	Returns a log4cpp managed logger instance.
			///
			/// Author:	Tobias Stein
			///
			/// Date:	23/09/2017
			///
			/// Parameters:
			/// logger - 	The logger.
			///
			/// Returns:	Null if it fails, else the logger.
			///-------------------------------------------------------------------------------------------------

			ECS_API Log::Logger* GetLogger(const char* logger);
#endif
		}
	}

	namespace Memory
	{
		namespace Internal
		{
			class  MemoryManager;
			extern MemoryManager*				ECSMemoryManager;
		}
	}

	namespace Event
	{
		class EventHandler;
	}


	class EntityManager;
	class SystemManager;
	class ComponentManager;



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



	class ECSEngine;

	ECS_API extern ECSEngine*		ECS_Engine;

	ECS_API void					Initialize();
	ECS_API void					Terminate();


	constexpr float TIME_STEP = 1.0f / 60.0f;

} // namespace ECS

#endif // __ECS_API_H__