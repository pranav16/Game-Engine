#pragma once
#ifndef FILEREAD_H
#define FILEREAD_H
#include <Windows.h>
namespace Engine
{


	class FileRead
	{
	public:
		static FileRead* getInstance();
		~FileRead();
		HANDLE createThread();
		void Resume();
		static DWORD WINAPI LoadThreadFunction(void * i_pThreadData);
	private:
		static FileRead* fileReadInstance;
		FileRead();
		HANDLE readThreadHandle;
	};
}


#endif