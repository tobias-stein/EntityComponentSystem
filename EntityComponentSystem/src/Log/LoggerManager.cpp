///-------------------------------------------------------------------------------------------------
/// File:	src\Log\LoggerManager.cpp.
///
/// Summary:	Implements the logger manager class.

#if !ECS_DISABLE_LOGGING

#include "Log/LoggerManager.h"
#include "Log/Logger.h"

#include "log4cplus/layout.h"
#include "log4cplus/ConsoleAppender.h"
#include "log4cplus/FileAppender.h"

namespace ECS { namespace Log { namespace Internal {

	LoggerManager::LoggerManager()
	{
		log4cplus::initialize();

		// create a conversion pattern
		const log4cplus::tstring PATTERN = LOG4CPLUS_TEXT(LOG_PATTERN);

		// create console log output
		log4cplus::SharedAppenderPtr consoleApp(new log4cplus::ConsoleAppender());
		consoleApp->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(PATTERN)));

		// create log file output
		log4cplus::SharedAppenderPtr fileApp(new log4cplus::FileAppender(LOG4CPLUS_TEXT(LOG_FILE_NAME)));
		fileApp->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(PATTERN)));

		// get root logger
		this->m_RootLogger = log4cplus::Logger::getRoot();

		// set root log level
		this->m_RootLogger.setLogLevel(log4cplus::ALL_LOG_LEVEL);

		// add appenders
		this->m_RootLogger.addAppender(consoleApp);
		this->m_RootLogger.addAppender(fileApp);
	}

	LoggerManager::~LoggerManager()
	{
		// cleanup logger
		for (auto& it : this->m_Cache)
		{
			delete it.second;
			it.second = nullptr;
		}

		log4cplus::Logger::getRoot().shutdown();
		log4cplus::threadCleanup();
	}

	Logger* LoggerManager::GetLogger(const char* name)
	{
		auto it = this->m_Cache.find(name);
		if (it == this->m_Cache.end())
		{		
			this->m_Cache.insert(std::make_pair<std::string, Logger*>(name, new Logger(this->m_RootLogger.getInstance(name))));
		}

		return this->m_Cache[name];
	}

}}} // namespace ECS::Log::Internal

#endif // !ECS_DISABLE_LOGGING