#ifndef _MUTEX_H
#define	_MUTEX_H
#include "WaitableObject.h"
namespace Engine
{


	class MutexLock : public WaitableObject
	{
	public:

		inline ~MutexLock();
		inline MutexLock(const WCHAR * i_pName);
		inline bool TryLock(void);
		inline void Lock(void);
		inline void Release(void);

	};

}

#include "MutexLockInline.h"
#endif
