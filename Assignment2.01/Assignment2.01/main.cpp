#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG
#include "Engine.h"
#include "../GLib/GLib.h"
#include <iostream>
#include "Timer.h"
#include "ConsolePrint.h"
#include "StringPool.h"
#include "Matrix4.h"


void unitTestForStringPool()
{
	Engine::StringPool::create(1024);
	const char* r = Engine::StringPool::getInstance()->add("Pranav");
	const char* p = Engine::StringPool::getInstance()->find("Pranav");
	MessagedAssert(p == r, "string pool not working")
	const char* q = Engine::StringPool::getInstance()->add("Pranav");
	MessagedAssert(p == q, "string pool not working")
	const char* s = Engine::StringPool::getInstance()->find("Pranavs");
	MessagedAssert(s == nullptr, "string pool find not working");
	
}

void unitTestForMatrix()
{
	Engine::Matrix4 matrix = Engine::Matrix4::CreateScale(2.0f, 2.0f, 2.0f);				
	Engine::Vector4 shipPoint(10.0f,10.0f,0.0f,1.0f);
	Engine::Vector4 scaledColoumShipPoint = matrix.MultiplyRight(shipPoint);
	matrix.Transpose();
	Engine::Vector4 scaledRowShipPoint = matrix.MultiplyLeft(shipPoint);
	if (scaledColoumShipPoint == scaledRowShipPoint)
	{
		
		Engine::Matrix4 rottransform = Engine::Matrix4::CreateZRotationCV(20.0f);
		Engine::Matrix4 translatetTransform = Engine::Matrix4::CreateTranslationCV(Engine::Vector(10.0f,10.0f,1.0f));
		Engine::Matrix4 finalTansform = translatetTransform * rottransform;
		shipPoint = finalTansform.MultiplyRight(shipPoint);
	}
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{

	bool isSuccess = Engine::EngineMain::getInstance()->init(i_hInstance, i_hPrevInstance,i_lpCmdLine,i_nCmdShow);
	bool bQuit = false;
	Engine::Timer timer;
	timer.setFrequencyForSystem();
	double dt = 16.0f;
	unitTestForMatrix();
	DWORD word = 10;


    while (true && !bQuit)
	{
		timer.startTimer();
		GLib::Service(bQuit);
		Engine::EngineMain::getInstance()->run(dt);
		timer.calculateFrameTimeInMs();
		dt = timer.getframeTimeInMs();
		
	}

	Engine::EngineMain::getInstance()->shutDown();

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}