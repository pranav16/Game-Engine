#ifndef _WAITABLE_OBJECT_H
#define _WAITABLE_OBJECT_H
#include <Windows.h>

namespace Engine
{
	class WaitableObject
	{
	public:
		WaitableObject() :
			m_Handle(INVALID_HANDLE_VALUE)
		{

		}

		HANDLE GetHandle(void) { return m_Handle; }

	protected:
		HANDLE					m_Handle;

	};

}

#endif // !_WAITABLE_OBJECT_H

