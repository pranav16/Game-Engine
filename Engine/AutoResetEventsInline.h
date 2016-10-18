#ifndef _AUTORESETEVENTSINLINE_H
#define _AUTORESETEVENTSINLINE_H
#include <Windows.h>
#include "AutoResetEvents.h"
#include "Assert.h"
namespace Engine
{

	AutoResetEvents::AutoResetEvents(const WCHAR * i_pName, bool i_bInitiallySignaled)
	{
		m_Handle = CreateEvent(NULL, FALSE, i_bInitiallySignaled, i_pName);
		MessagedAssert(m_Handle != INVALID_HANDLE_VALUE,"could not create auto reset event");
	}

	AutoResetEvents::~AutoResetEvents()
	{
		CloseHandle(m_Handle);
	}

	bool AutoResetEvents::WaitFor(void)
	{
		DWORD result = WaitForSingleObject(m_Handle, INFINITE);
		MessagedAssert(result == WAIT_OBJECT_0,"could not wait on object");

		return true;
	}

	void AutoResetEvents::Signal(void)
	{
		BOOL result = SetEvent(m_Handle);
		MessagedAssert(result == TRUE,"signal failed");
	}



}


#endif