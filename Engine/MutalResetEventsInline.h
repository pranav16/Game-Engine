#ifndef _MUTAUL_RESET_EVENT_INLINE_
#define _MUTAUL_RESET_EVENT_INLINE_
#include "ManualRestEvent.h"
#include "Assert.h"
#include  <Windows.h>
namespace Engine
{
	inline MutalResetEvents::MutalResetEvents(const WCHAR * i_pName, bool i_bInitiallySignaled)
	{
		m_Handle = CreateEvent(NULL, TRUE, i_bInitiallySignaled, i_pName);
		MessagedAssert(m_Handle != INVALID_HANDLE_VALUE,"failed to create reset events");
	}

	inline MutalResetEvents::~MutalResetEvents()
	{
		CloseHandle(m_Handle);
	}

	inline void MutalResetEvents::Reset(void)
	{
		ResetEvent(m_Handle);
	}

	inline bool MutalResetEvents::WaitFor(void)
	{
		DWORD result = WaitForSingleObject(m_Handle, INFINITE);
		MessagedAssert(result == WAIT_OBJECT_0,"could not wait on events");

		return true;
	}

	inline void MutalResetEvents::Signal(void)
	{
		BOOL result = SetEvent(m_Handle);
		MessagedAssert(result == TRUE,"could not create a signal");
	}







}











#endif