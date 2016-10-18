#include "HeapManager.h"
#include <algorithm>
#include "Assert.h"
namespace Engine
{

	inline HeapManager::HeapManager()
	{
		 maxHeapSize = 0;
		 listOfAllocatedNodes = nullptr;
		 listOfFreeNodes = nullptr;
		 memoryBlock = nullptr;
	
	}
	 inline HeapManager* HeapManager::getHeapManager()
	{
		if (manager == nullptr)
		{
			void* memBlock = malloc(sizeof(HeapManager));
			manager = new (memBlock)HeapManager();
			const size_t 		sizeHeap = 1024 * 1024;
			const unsigned int 	numDescriptors = 2048;
			// Allocate memory for my test heap.
			void * pHeapMemory = _aligned_malloc(sizeHeap, 4);
			MessagedAssert(pHeapMemory != nullptr, "out of memory");
			manager->create(pHeapMemory, sizeHeap, numDescriptors);
			return manager;
		}
		return manager;
	}
	 




}