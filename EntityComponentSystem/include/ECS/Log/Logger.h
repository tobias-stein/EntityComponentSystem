/*
	Author : Tobias Stein
	Date   : 11th September, 2016
	File   : Logger.h
	
	Class that manages the logging.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Platform.h"

#include "log4cplus/logger.h"
#include "log4cplus/loggingmacros.h"

#if !ECS_DISABLE_LOGGING

namespace ECS { namespace Log {

		class ECS_API Logger
		{		
			Logger(const Logger&) = delete;
			Logger& operator=(Logger&) = delete;
			
			log4cplus::Logger m_logger;
			

		public:

			explicit Logger(log4cplus::Logger& logger);

			~Logger();

			// trace 
			template<typename... Args>
			inline void LogTrace(const char* fmt, Args... args)
			{			
				LOG4CPLUS_TRACE_FMT(this->m_logger, (const log4cplus::tchar*)fmt, std::forward<Args>(args)...);
			}

			// debug
			template<typename... Args>
			inline void LogDebug(const char* fmt, Args... args)
			{
				LOG4CPLUS_DEBUG_FMT(this->m_logger, fmt, std::forward<Args>(args)...);
			}

			// info
			template<typename... Args>
			inline void LogInfo(const char* fmt, Args... args)
			{
				LOG4CPLUS_INFO_FMT(this->m_logger, fmt, std::forward<Args>(args)...);
			}

			// warn
			template<typename... Args>
			inline void LogWarning(const char* fmt, Args... args)
			{
				LOG4CPLUS_WARN_FMT(this->m_logger, fmt, std::forward<Args>(args)...);
			}

			// error
			template<typename... Args>
			inline void LogError(const char* fmt, Args... args)
			{
				LOG4CPLUS_ERROR_FMT(this->m_logger, fmt, std::forward<Args>(args)...);
			}

			// fatal
			template<typename... Args>
			inline void LogFatal(const char* fmt, Args... args)
			{
				LOG4CPLUS_FATAL_FMT(this->m_logger, fmt, std::forward<Args>(args)...);
			}

		}; // class Logger


}} // namespace ECS::Log

#endif // !ECS_DISABLE_LOGGING

#include "Log/LoggerMacro.h"

#endif // __LOGGER_H__
