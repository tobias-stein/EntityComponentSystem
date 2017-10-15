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

private:
	
	FrameCount			m_FrameCount;
	FrameCount			m_LastFPS;
	Clock::time_point	m_LastUpdate;


public:

	FPS();
	~FPS();

	void Update();

	float GetFPS() const;

}; // class FPS

#endif // __FRAMES_PER_SECOND_H__
