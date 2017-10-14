#include "FPS.h"

FPS::FPS()
{
	this->m_Samples.reserve(MAX_SAMPLES);
	this->m_SampleIndex = 0;
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
		if (this->m_Samples.size() < MAX_SAMPLES)
		{
			this->m_Samples.push_back(this->m_FrameCount);
			this->m_SampleIndex++;
		}
		else
		{
			if (this->m_SampleIndex < MAX_SAMPLES)
			{
				this->m_Samples[this->m_SampleIndex++] = this->m_FrameCount;
			}
			else
			{
				this->m_SampleIndex = 0;
				this->m_Samples[this->m_SampleIndex] = this->m_FrameCount;
			}		
		}

		// reset frame count
		this->m_FrameCount = 0;

		this->m_LastUpdate = now;
	}
}

float FPS::GetFPS() const
{
	uint32_t sum = 0;
	size_t sampleCount = this->m_Samples.size();

	if (sampleCount == 0)
		return 0.0f;

	for (auto s : this->m_Samples)
		sum += s;

	return sum / sampleCount;
}
