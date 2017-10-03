///-------------------------------------------------------------------------------------------------
/// File:	src\util\Timer.cpp.
///
/// Summary:	Implements the timer class.
///-------------------------------------------------------------------------------------------------

#include "util/Timer.h"

namespace ECS { namespace util {

	Timer::Timer() :
		m_Elapsed(0)
	{}

	Timer::~Timer()
	{}

	void Timer::Tick(DurationRep ms)
	{
		this->m_Elapsed += std::chrono::duration<DurationRep>(ms);
	}

	void Timer::Reset()
	{
		this->m_Elapsed = Elapsed::zero();
	}

}} // namespace ECS::util