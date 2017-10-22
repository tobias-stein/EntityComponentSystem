///-------------------------------------------------------------------------------------------------
/// File:	FPS.h.
///
/// Summary:	Declares the FPS class.
///-------------------------------------------------------------------------------------------------

#ifndef __FRAMES_PER_SECOND_H__
#define __FRAMES_PER_SECOND_H__

#include <chrono>
#include <vector>
class FPS
{
	using Clock			= std::chrono::steady_clock;
	using FrameCount	= uint32_t;
	using FrameTime		= std::chrono::duration<float>;

	static constexpr FrameTime INTERVAL { FrameTime(1) };

private:
	
	Clock::time_point	m_LastUpdate;

	FrameCount			m_FrameCount;
	FrameTime			m_AccFrameTime;

	FrameCount			m_CurrentFPS;

public:

	FPS();
	~FPS();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	float FPS::Update();
	///
	/// Summary:	Updates this object.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	22/10/2017
	///
	/// Returns:	A float that specifies the delta time since last update.
	///-------------------------------------------------------------------------------------------------

	float Update();

	float GetFPS() const;

}; // class FPS

#endif // __FRAMES_PER_SECOND_H__
