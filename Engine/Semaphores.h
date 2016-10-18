#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H
#include "WaitableObject.h"
namespace Engine
{


class Semaphore :public WaitableObject
{

public:
	inline Semaphore(const WCHAR * i_pName, unsigned int i_CountMax, unsigned int i_CountInit);
	inline ~Semaphore();

	inline void Increment(unsigned int i_count = 1);
	inline void WaitAndDecrement(void);



};


}
#include "SemaphoreInline.h"
#endif