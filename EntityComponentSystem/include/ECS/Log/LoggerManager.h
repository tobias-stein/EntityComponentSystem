///-------------------------------------------------------------------------------------------------
/// File:	include\Log\LoggerManager.h.
///
/// Summary:	Declares the logger manager class.

#pragma once

#if !ECS_DISABLE_LOGGING

#ifndef __LOGGER_MANAGER_H__
#define __LOGGER_MANAGER_H__


#include "Platform.h"

// Log4cplus logger support
#include "log4cplus/logger.h"

namespace ECS { namespace Log { 
	
	class Logger;

	namespace Internal {

	

	class LoggerManager
	{
		using LoggerCache = std::unordered_map<std::string, Logger*>;

		static constexpr const char* LOG_FILE_NAME = "ECS.log";
		static constexpr const char* DEFAULT_LOGGER = "ECS";
		static constexpr const char* LOG_PATTERN = "%d{%H:%M:%S,%q} [%t] %-5p %c{1} %x- %m%n";

		// This class is not inteeded to be initialized
		LoggerManager(const LoggerManager&) = delete;
		LoggerManager& operator=(LoggerManager&) = delete;

		// root logger
		log4cplus::Logger m_RootLogger;


		/// Summary:	Holds all acquired logger
		LoggerCache m_Cache;

	public:

		LoggerManager();
		~LoggerManager();


		Logger* GetLogger(const char* logger = DEFAULT_LOGGER);

	}; // class LoggerManager

}}} // namespace ECS::Log::Internal


#endif // __LOGGER_MANAGER_H__
#endif // !ECS_DISABLE_LOGGING