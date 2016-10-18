#include "Allocators.h"
#include "Assert.h"
#include "Lock.h"
#include "MutexLock.h"
	// standard new / delete
	void * operator new(size_t i_size)
	{
		using namespace Engine;
	    MutexLock lock(L"HEAPLOCK");

		HeapManager * manager = HeapManager::getHeapManager();
		MessagedAssert(manager != nullptr, "heap is not instatiate before calling new");

		return manager->alloc(i_size);
	}
		void operator delete(void * i_ptr)
	{

		using namespace Engine;
		MutexLock lock(L"HEAPLOCK");
		MessagedAssert(i_ptr != nullptr, "trying to delete null");
		FixedSizeAllocator* fixedAllocator = FixedSizeAllocator::getInstance();
		if (fixedAllocator->isInRange(reinterpret_cast<uint8_t*>(i_ptr)))
		{
			fixedAllocator->freeMemory(i_ptr);
		}
		else
		{
			HeapManager * manager = HeapManager::getHeapManager();
			MessagedAssert(manager != nullptr, "heap is null in delete");
			manager->freeMemory(i_ptr);

		}
	}

	// standard array new / delete
	void * operator new[](size_t i_size)
	{
		using namespace Engine;
		MutexLock lock(L"HEAPLOCK");
		HeapManager * manager = HeapManager::getHeapManager();
		MessagedAssert(manager != nullptr, "heap is not instatiate before calling new");

		return manager->alloc(i_size);
	}
	void operator delete[](void * i_ptr)
	{
		using namespace Engine;
		MutexLock lock(L"HEAPLOCK");
		MessagedAssert(i_ptr != nullptr, "trying to delete null");
		FixedSizeAllocator* fixedAllocator = FixedSizeAllocator::getInstance();
		if (fixedAllocator->isInRange(reinterpret_cast<uint8_t*>(i_ptr)))
		{
			fixedAllocator->freeMemory(i_ptr);
		}
		else
		{
			HeapManager * manager = HeapManager::getHeapManager();
			MessagedAssert(manager != nullptr, "heap is null in delete");
			manager->freeMemory(i_ptr);

		}
	}

	
	void * operator new(size_t i_size, NewAlignment i_align)
	{

		using namespace Engine;
		MutexLock lock(L"HEAPLOCK");
		switch (i_align)
		{

		case NewAlignment::NEW_ALIGN_16:
		{
			FixedSizeAllocator* allocator = FixedSizeAllocator::getInstance();
			MessagedAssert(allocator != nullptr, "allocator is null in new");
			return allocator->alloc();

		}
		default:
			Engine::HeapManager* heap = Engine::HeapManager::getHeapManager();
			MessagedAssert(heap != nullptr, "default heap is null");
			return heap->alloc(i_size);

		}

	}
	void operator delete(void * i_ptr, NewAlignment i_align)
	{

		using namespace Engine;
		MutexLock lock(L"HEAPLOCK");
		switch (i_align)
		{

		case NewAlignment::NEW_ALIGN_16:
		{
			FixedSizeAllocator* allocator = FixedSizeAllocator::getInstance();
			MessagedAssert(allocator != nullptr, "allocator is null in new");
			allocator->freeMemory(i_ptr);
			break;
		}
		default:
			HeapManager* heap = HeapManager::getHeapManager();
			MessagedAssert(heap != nullptr, "default heap is null");
			heap->freeMemory(i_ptr);
			break;
		}
}
	

