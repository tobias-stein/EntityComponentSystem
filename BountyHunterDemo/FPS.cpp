#include "FPS.h"

FPS::FPS()
{
	this->m_CurrentFPS = 0.0f;

	this->m_LastUpdate = Clock::now();

	this->m_FrameCount = 0;
	this->m_AccFrameTime = std::chrono::seconds(0);
}

FPS::~FPS()
{
}

float FPS::Update()
{
	this->m_FrameCount++;

	const Clock::time_point now = Clock::now();

	const FrameTime DT = std::chrono::duration_cast<FrameTime>(now - this->m_LastUpdate);
	this->m_AccFrameTime += DT;

	this->m_LastUpdate = now;

	if (this->m_AccFrameTime > INTERVAL)
	{
		this->m_CurrentFPS = this->m_FrameCount;

		// reset frame count
		this->m_FrameCount = 0;

		// reset frame time
		this->m_AccFrameTime = FrameTime(0);
	}

	// return dt as seconds
	return DT.count();
}

float FPS::GetFPS() const
{
	return this->m_CurrentFPS;
}
