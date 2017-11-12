/*
	Author : Tobias Stein
	Date   : 11th September, 2016
	File   : Logger.cpp
	
	Class that manages the logging.

	All Rights Reserved. (c) Copyright 2016.
*/

#if !ECS_DISABLE_LOGGING

#include "Log/Logger.h"

namespace ECS { namespace Log {
	
	Logger::Logger(log4cplus::Logger& logger) :
		m_logger(logger)
	{}
	
	Logger::~Logger()
	{}

}} // namespace ECS::Log

#endif // !ECS_DISABLE_LOGGING