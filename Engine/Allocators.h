#ifndef __ALLOCATORS_H
#define __ALLOCATORS_H

#include "HeapManager.h"
#include "FixedSizeAllocator.h"
	// standard new / delete

	void * operator new(size_t i_size);
	void operator delete(void * i_ptr);

	// standard array new / delete
	void * operator new[](size_t i_size);
	void operator delete[](void * i_ptr);

	// standard placement array new / delete
	void * operator new(size_t i_size, void * i_pmem);
	void operator delete(void * i_ptr, void * i_pmem);

	// standard array placement array new / delete
	void * operator new[](size_t i_size, void * i_pmem);
	void operator delete[](void * i_ptr, void * i_pmem);

	// custom alignment allocators
	enum NewAlignment
	{
		NEW_ALIGN_DEFAULT,
		NEW_ALIGN_16 = 16,
		NEW_ALIGN_32 = 32
	};

	void * operator new(size_t i_size, NewAlignment i_align);
	void operator delete(void * i_ptr, NewAlignment i_align);





#endif // __ALLOCATORS_H