#include "FPS.h"

FPS::FPS()
{
	this->m_LastFPS = 0;
	this->m_FrameCount = 0;
	this->m_LastUpdate = Clock::now();
}

FPS::~FPS()
{
}

void FPS::Update()
{
	this->m_FrameCount++;


	const Clock::time_point now = Clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - this->m_LastUpdate).count() > 1000)
	{
		this->m_LastFPS = this->m_FrameCount;

		// reset frame count
		this->m_FrameCount = 0;

		this->m_LastUpdate = now;
	}
}

float FPS::GetFPS() const
{
	return this->m_LastFPS;
}
