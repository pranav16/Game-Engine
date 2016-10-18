#pragma once
#include "Timer.h"

#define DESIRED_FPS		60.0f
#define DESIRED_FRAMETIME_MS	(1000.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS	(2 * DESIRED_FRAMETIME_MS)
#define CLAMP_FRAMETIME true

namespace Engine
{

	inline void Timer::startTimer()
	{
		QueryPerformanceCounter(&g_startTimeInMs);
	}
	inline void Timer::setFrequencyForSystem()
	{
		QueryPerformanceFrequency(&g_systemFrequency);
	}

	inline void Timer::calculateFrameTimeInMs()
	{
		LARGE_INTEGER endTime;
		QueryPerformanceCounter(&endTime);
		g_frameTimeInMs = (endTime.QuadPart - g_startTimeInMs.QuadPart) * 1000.f / g_systemFrequency.QuadPart;
	}
	inline double Timer::getframeTimeInMs() const
	{
#if defined( CONSTANT_FRAMETIME )
		return DESIRED_FRAMETIME_MS;
#elif defined( CLAMP_FRAMETIME )
		if (g_frameTimeInMs > MAX_FRAMETIME_MS)
			return MAX_FRAMETIME_MS;
		else
			return g_frameTimeInMs;
#else
		return g_frameTimeInMs;
#endif
	}



}