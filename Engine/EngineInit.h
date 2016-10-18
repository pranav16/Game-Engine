#pragma once
#include "Engine.h"
#include <algorithm>
namespace Engine
{
	EngineMain* EngineMain::getInstance()
	{
		if (myInstance == nullptr)
		{
			void* memBlock = malloc(sizeof(EngineMain));
			myInstance = new(memBlock)EngineMain();
			return myInstance;
		}
		return myInstance;
	}
	inline EngineMain::EngineMain()
	{

	}
}