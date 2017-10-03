///-------------------------------------------------------------------------------------------------
/// File:	include\util\Timer.h.
///
/// Summary:	Declares the Timer class.
///-------------------------------------------------------------------------------------------------

#ifndef __TIMER_H___
#define __TIMER_H___

#include "API.h"

namespace ECS { namespace util {

	class ECS_API Timer
	{
#ifdef ECS_64BIT	
		using DurationRep = f64;
#else
		using DurationRep = f32;
#endif

		using Elapsed = std::chrono::duration<DurationRep, std::milli>;

	private:

		Elapsed m_Elapsed;

	public:

		Timer();
		~Timer();

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void Timer::Tick(DurationRep ms);
		///
		/// Summary:	Advances timer by adding elapsed milliseconds.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	3/10/2017
		///
		/// Parameters:
		/// ms - 	milliseconds (can be fractions).
		///-------------------------------------------------------------------------------------------------

		void Tick(DurationRep ms);

		///-------------------------------------------------------------------------------------------------
		/// Fn:	void Timer::Reset();
		///
		/// Summary:	Resets this timer to zero.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	3/10/2017
		///-------------------------------------------------------------------------------------------------

		void Reset();

		///-------------------------------------------------------------------------------------------------
		/// Fn:	inline TimeStamp Timer::GetTimeStamp() const
		///
		/// Summary:	Gets a TimeStamp from current timer value.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	3/10/2017
		///
		/// Returns:	The time stamp.
		///-------------------------------------------------------------------------------------------------

		inline TimeStamp GetTimeStamp() const
		{
			DurationRep tickCount = this->m_Elapsed.count();
			return *((TimeStamp*)(&tickCount));
		}

	}; // class Timer

}} // namespace ECS::util

#endif // __TIMER_H___

