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

	void Timer::Tick(float ms)
	{
		this->m_Elapsed += std::chrono::duration<float, std::ratio<1, 1000>>(ms);
	}

	void Timer::Reset()
	{
		this->m_Elapsed = Elapsed::zero();
	}

}} // namespace ECS::util