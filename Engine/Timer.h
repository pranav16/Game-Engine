#pragma once
#ifndef _Timer_H
#define _Timer_H
#include <Windows.h>
namespace Engine
{
	class Timer
	{
		LARGE_INTEGER  g_startTimeInMs;
		double  g_frameTimeInMs;
		LARGE_INTEGER  g_systemFrequency;
	
	public:
		Timer() :g_startTimeInMs({ 0 }), g_frameTimeInMs(0.0f), g_systemFrequency({ 0 }) {};
		inline void startTimer();
		inline void setFrequencyForSystem();
		inline void calculateFrameTimeInMs();
		inline double getframeTimeInMs()  const;
	};



}
#include "Timer_Ini.h"
#endif




