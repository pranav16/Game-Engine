#pragma once
#ifndef FILE_DATA_TO_ACTOR_H
#define FILE_DATA_TO_ACTOR_H
#include <Windows.h>
namespace Engine
{


	class FileDataToActor
	{
	public:
		static FileDataToActor* getInstance();
		~FileDataToActor();
		HANDLE createThread();
		void Resume();
		static DWORD WINAPI ProcessThreadFunction(void * i_pThreadData);
	private:
		static FileDataToActor* fileProcessInstance;
		FileDataToActor();
		HANDLE processThreadHandle;
	};
}


#endif