#ifndef _SEMAPHOREINLINE_H
#define _SEMAPHOREINLINE_H
#include "Semaphores.h"
#include "Assert.h"
#include <Windows.h>
namespace Engine
{

	inline Semaphore::Semaphore(const WCHAR * i_pName, unsigned int i_CountMax, unsigned int i_CountInit)
	{
		MessagedAssert(i_CountInit <= i_CountMax,"intialisation of semaphore with value higher than max number of permits");

		m_Handle = CreateSemaphore(NULL, i_CountInit, i_CountMax, i_pName);
		MessagedAssert(m_Handle != NULL,"failed to create semaphore")
			
	}

	inline Semaphore::~Semaphore()
	{
		BOOL result = CloseHandle(m_Handle);
		MessagedAssert(result == TRUE,"could not close semaphore");
	}

	// should 
	inline void Semaphore::Increment(unsigned int i_count)
	{
		BOOL result = ReleaseSemaphore(m_Handle, i_count, NULL);
		MessagedAssert(result == TRUE,"could not increment semaphore");
	}

	inline void Semaphore::WaitAndDecrement(void)
	{
		DWORD result = WaitForSingleObject(m_Handle, INFINITE);
		MessagedAssert(result == WAIT_OBJECT_0,"could not decement semaphore");
	}


}




#endif