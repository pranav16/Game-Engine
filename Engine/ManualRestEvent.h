#ifndef _MUTAUL_RESET_EVENT_
#define _MUTAUL_RESET_EVENT_
#include "WaitableObject.h"
namespace Engine
{
class MutalResetEvents : public WaitableObject
{
public:
	inline MutalResetEvents(const WCHAR * i_pName, bool i_bInitiallySignaled);
	inline ~MutalResetEvents();

	inline void Reset(void);
	
	inline bool WaitFor(void);
	inline void Signal(void);


};

}
#include "MutalResetEventsInline.h"





#endif // _MUTAUL_RESET_EVENT_