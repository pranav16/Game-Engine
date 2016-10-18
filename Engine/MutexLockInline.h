#ifndef _MUTEXINLINE_H
#define _MUTEXINLINE_H


#include "MutexLock.h"
#include "assert.h"
#include <windows.h>

namespace Engine
{


	inline  MutexLock::~MutexLock()
	{
		BOOL result = CloseHandle(m_Handle);
		MessagedAssert(result == TRUE,"could not close the mutex")
	}
	inline MutexLock::MutexLock(const WCHAR * i_pName)
	{
		m_Handle = CreateMutex(NULL, FALSE, i_pName);
		MessagedAssert(m_Handle != NULL,"fail to create mutex");
	}
	inline bool MutexLock::TryLock(void)
	{
		DWORD result = WaitForSingleObject(m_Handle, 0);

		return result == WAIT_OBJECT_0;
	}
	inline void MutexLock::Lock(void)
	{
		DWORD result = WaitForSingleObject(m_Handle, INFINITE);
		MessagedAssert(result == WAIT_OBJECT_0,"failed to lock mutex");
	}
	inline void MutexLock::Release(void)
	{
		BOOL result = ReleaseMutex(m_Handle);
		MessagedAssert(result == TRUE,"failed to release mutex");
	}



}
#endif // !_MUTEXINLINE_H