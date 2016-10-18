#ifndef HEAP_MANAGER
#define HEAP_MANAGER
#include <stdint.h>
#include <inttypes.h>
namespace Engine
{ 
class HeapManager
{

	struct MemoryBlockDescriptor
	{
		size_t m_numberOfBytres;
		uint8_t* pMemBlock;
		struct MemoryBlockDescriptor* m_nextNode;
	};

	typedef struct MemoryBlockDescriptor MemoryDescriptor;
	public:
		 inline static HeapManager* getHeapManager();
		 void* alloc(const size_t size);
		 void create(void* memory,const size_t size,const unsigned int numberOfDescriptors);
		 bool freeMemory(const void* freeBlock);
		 void deleteHeap();
		 void collectBlocks();
		 ~HeapManager();
		
private:
	void* getFreeDescriptor();
	void removeNodeFromFreeList(MemoryDescriptor* descriptor);
	void removeNodeFromAllocatedList(MemoryDescriptor* descriptor);
	void addSequentiallyToFreeList(MemoryBlockDescriptor* descriptor);
	bool checkIfDescriptorAlreadyPresentInFreeList(const MemoryBlockDescriptor* descriptor);
	bool checkIfDescriptorAlreadyPresentInAllocatedList(const MemoryBlockDescriptor* descriptor);
	void addToEndOfFreeList(MemoryDescriptor* descriptor);
	bool checkForSequentialFreeBlocks();
	int sizeOfFreeList();
	int sizeOfAllocatedList();
	static HeapManager* manager;
	size_t maxHeapSize;
	size_t currentHeapSize;
	MemoryBlockDescriptor* listOfFreeNodes;
	MemoryBlockDescriptor* listOfAllocatedNodes;
	HeapManager& operator=(const HeapManager& manager){};
	HeapManager(const HeapManager& manager){};
	inline HeapManager();
	void* memoryBlock;

};
}
#include "HeapManagerInline.h"

#endif