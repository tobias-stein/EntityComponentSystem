///-------------------------------------------------------------------------------------------------
/// File:	include\API.h.
///
/// Summary:	API.

#pragma once


#include "Platform.h"

#include "Log/Logger.h"




namespace ECS 
{

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
	ECS_API Log::Logger* GetLogger(const char* logger);




	namespace Memory
	{
		namespace Internal
		{
			class MemoryManager;
		}

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

			std::shared_ptr<Internal::MemoryManager> ECS_MEMORY_MANAGER;

		public:

			GlobalMemoryUser();

			virtual ~GlobalMemoryUser();

			inline const void* Allocate(size_t memSize, const char* user = nullptr);
			inline void Free(void* pMem);
		};

	} // namespace ECS::Memory

} // namespace ECS