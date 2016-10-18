#ifndef _LOCK_H
#define _LOCK_H
#include "MutexLock.h"
namespace Engine
{


	class Lock
	{
	public:
		inline Lock(MutexLock &lock) : m_mutex(lock) { m_mutex.Lock(); };
		inline ~Lock() { m_mutex.Release(); };

	private:
		MutexLock m_mutex;
	};


}



#endif