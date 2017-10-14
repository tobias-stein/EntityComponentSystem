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
	static constexpr size_t MAX_SAMPLES { 3 };

	using Samples		= std::vector<uint32_t>;

	using Clock			= std::chrono::steady_clock;

	using FrameCount	= uint32_t;

private:

	Samples				m_Samples;
	size_t				m_SampleIndex;

	FrameCount			m_FrameCount;
	Clock::time_point	m_LastUpdate;


public:

	FPS();
	~FPS();

	void Update();

	float GetFPS() const;

}; // class FPS

#endif // __FRAMES_PER_SECOND_H__
