#include "ThreadedFileProcessor.h"
#include "Assert.h"
#include "Lock.h"
#include "MutexLock.h"
#include <iostream>
namespace Engine
{
	 const char* ThreadedFileRead::m_filePath;
	 DWORD ThreadedFileRead::ThreadId;
	 HANDLE ThreadedFileRead::m_handle;
	DWORD WINAPI ThreadedFileRead::entry(void * i_pThreadParameters)
	{
		MessagedAssert(m_filePath != nullptr, "filepath cannot be null");
		size_t bytesRead;
		LoadFile(m_filePath,bytesRead);

	}
	uint8_t* ThreadedFileRead::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
	{
		const WCHAR *mutexName;
		int nChars = MultiByteToWideChar(CP_ACP, 0, i_pFilename, -1, NULL, 0);
		mutexName = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, i_pFilename, -1, (LPWSTR)mutexName, nChars);
		MessagedAssert(mutexName !=nullptr,"could not conver to wchar");
		MutexLock mlock(mutexName);
		Lock lock(mlock);
		delete mutexName;
		FILE * pFile = NULL;
		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;
		MessagedAssert(pFile != NULL, "file could not be opened");
		int FileIOError = fseek(pFile, 0, SEEK_END);
		MessagedAssert(FileIOError == 0, "FileIOError");
		long FileSize = ftell(pFile);
		MessagedAssert(FileSize >= 0, "Filesize is less that zero");
		FileIOError = fseek(pFile, 0, SEEK_SET);
		MessagedAssert(FileIOError == 0, "FileIOError");
		uint8_t * pBuffer = new uint8_t[FileSize];
		MessagedAssert(pBuffer != nullptr, "buffer could not be created");
		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		MessagedAssert(FileRead == FileSize, "Filesize read is not equal to filesize");
		fclose(pFile);
		o_sizeFile = FileSize;
		return pBuffer;
	}
	ThreadedFileRead::~ThreadedFileRead()
	{

	}
	 bool ThreadedFileRead::suspend()
	{
		MessagedAssert(m_handle != INVALID_HANDLE_VALUE, "calling suspend on invalid thread");
		MessagedAssert(m_handle != nullptr, "calling suspend on invalid thread");
		SuspendThread(m_handle);
	}
	bool ThreadedFileRead::run()
	{
		
		m_handle = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)ThreadedFileRead::entry, NULL, CREATE_SUSPENDED, &ThreadId);
		MessagedAssert(m_handle != nullptr, "calling run on invalid thread");
		ResumeThread(m_handle);
		return true;
	}
	bool ThreadedFileRead::resume()
	{
		MessagedAssert(m_handle != INVALID_HANDLE_VALUE, "calling resume on invalid thread");
		MessagedAssert(m_handle != nullptr, "calling resume on invalid thread");
		ResumeThread(m_handle);
	}


}
