#ifndef _AUTORESETEVENTS_H
#define _AUTORESETEVENTS_H
#include "WaitableObject.h"

namespace  Engine
{
	class AutoResetEvents : public WaitableObject
	{
		inline AutoResetEvents(const WCHAR * i_pName, bool i_bInitiallySignaled);
		inline ~AutoResetEvents();

		// We should add a wait timeout parameter but I'm in a hurry
		inline bool WaitFor(void);
		inline void Signal(void);

	};


}


#endif
