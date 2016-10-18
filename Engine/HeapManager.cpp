#include "HeapManager.h"
#include "Assert.h"
#include<algorithm>



using namespace Engine;

HeapManager* HeapManager::manager;


void  HeapManager::create(void* memory, const size_t size,const unsigned int numberOfDescriptors)
{
	MessagedAssert(memory != nullptr ,"Memory block can not be null");
	MessagedAssert(memoryBlock == nullptr, "Memory block being created once again!!");
	memoryBlock = memory;
	
	listOfFreeNodes = reinterpret_cast<MemoryDescriptor*>(memoryBlock);
	listOfFreeNodes->m_numberOfBytres = size - sizeof(listOfFreeNodes);
	listOfFreeNodes->m_nextNode = nullptr;
	listOfFreeNodes->pMemBlock = reinterpret_cast<uint8_t*>(listOfFreeNodes) + numberOfDescriptors * sizeof(listOfFreeNodes);
	maxHeapSize = size;
	currentHeapSize = size;
	MemoryDescriptor* currentNode = listOfFreeNodes;
	size_t sizeOfDescr = sizeof(listOfFreeNodes);
	for (unsigned int i = 0; i < numberOfDescriptors - 1; i++)
	{
		MemoryDescriptor* descriptor = currentNode + 1;
	    uint8_t* blockStart = reinterpret_cast<uint8_t*> (memoryBlock);
		uint8_t* descpStart = reinterpret_cast<uint8_t*> (descriptor);
		bool isOutOfBounds = descpStart >(blockStart + size);
		if (isOutOfBounds)
		{
			MessagedAssert(!isOutOfBounds, "you need more space!! or you need to reduce number of desciptors");
			break;
		}
		if (i == 683 || i == 682 || i == 684)
		{
			int j = 0;
		}
		currentNode->m_nextNode = descriptor;
		descriptor->m_numberOfBytres = 0;
		descriptor->m_nextNode = nullptr;
		descriptor->pMemBlock = nullptr;
		currentNode = descriptor;
	}
	
}
bool HeapManager::freeMemory(const void* freeBlock)
{
	MessagedAssert(freeBlock != nullptr, "passing a null to free");
	MemoryDescriptor* allocatedNodes = listOfAllocatedNodes;
	const uint8_t* addressofBlock = reinterpret_cast<const uint8_t*>(freeBlock);

	while (allocatedNodes)
	{
		if (allocatedNodes->pMemBlock == addressofBlock)
		{
			MessagedAssert(!checkIfDescriptorAlreadyPresentInFreeList(allocatedNodes), "re-freeing a same block")
				currentHeapSize += allocatedNodes->m_numberOfBytres;
			removeNodeFromAllocatedList(allocatedNodes);
			MessagedAssert(!checkIfDescriptorAlreadyPresentInAllocatedList(allocatedNodes), "unable to remove block from allocated list");
			addSequentiallyToFreeList(allocatedNodes);
			
			return true;
		}
		allocatedNodes = allocatedNodes->m_nextNode;
	}
	MessagedAssert(allocatedNodes != nullptr, "freeing a memory that was not allocated!");
	return false;

}
int count = 0;
void* HeapManager::alloc(const size_t size)
{
	count++;
	void* blockToReturn = nullptr;
	MessagedAssert(size < maxHeapSize, "trying to allocate memeory greater than the heap size! Try increasing the heap size!");
	if (currentHeapSize < size)
	{
		MessagedAssert(currentHeapSize > size, "Heap is out of memory , will need to add more memory!");
		return blockToReturn;
	}
	if (listOfFreeNodes == nullptr)
	{
		int y = sizeOfAllocatedList();
		MessagedAssert(listOfFreeNodes != nullptr, "Heap needs to be set up before allocating or you need more field descriptors");
		return blockToReturn;
	}
	size_t memoryNeeded = size;
	MemoryDescriptor* memDescripors = listOfFreeNodes;
	//find the node that fits well
	while (memDescripors)
	{
		if (memDescripors->m_numberOfBytres >= size)
		{
			blockToReturn = memDescripors->pMemBlock;
			break;
		}

		memDescripors = memDescripors->m_nextNode;
	}
	if (memDescripors == nullptr)
	{
		return nullptr;
	}
	//split the node if the size is big
	if (memDescripors->m_numberOfBytres > size)
	{
		MemoryDescriptor* descriptor = reinterpret_cast<MemoryDescriptor*>(getFreeDescriptor());
		if (descriptor)
		{
			descriptor->m_numberOfBytres = memDescripors->m_numberOfBytres - size;
			descriptor->pMemBlock = memDescripors->pMemBlock + size;
			memDescripors->m_numberOfBytres = size;
		}
	}

	//remove the block from freenodes
	removeNodeFromFreeList(memDescripors);
	MessagedAssert(!checkIfDescriptorAlreadyPresentInFreeList(memDescripors), "unable to remove the block of memory given to user from free list!");
	//add it to allocated nodes
	MemoryDescriptor* allocatedNodesNext = listOfAllocatedNodes;
	memDescripors->m_nextNode = allocatedNodesNext;
	listOfAllocatedNodes = memDescripors;
	currentHeapSize -= size;
	return blockToReturn;
}

bool HeapManager::checkIfDescriptorAlreadyPresentInFreeList(const MemoryBlockDescriptor* descriptor)
{
	return false;
	MemoryDescriptor* freeNodes = listOfFreeNodes;
	while (freeNodes)
	{
		if (freeNodes == descriptor)
			return true;
		freeNodes = freeNodes->m_nextNode;
	}

	return false;
}
bool HeapManager::checkIfDescriptorAlreadyPresentInAllocatedList(const MemoryBlockDescriptor* descriptor)
{
	MemoryDescriptor* freeNodes = listOfAllocatedNodes;
	while (freeNodes)
	{
		if (freeNodes == descriptor)
			return true;
		freeNodes = freeNodes->m_nextNode;
	}
	return false;
}

void HeapManager::collectBlocks()
{
	MemoryDescriptor* tempNode = listOfFreeNodes;
	if (listOfFreeNodes == nullptr)
		return;
	int i = 0;
	while (tempNode != nullptr && tempNode->m_nextNode != nullptr)
	{
		MemoryDescriptor* nextNode = tempNode->m_nextNode;
		if (tempNode->pMemBlock &&  nextNode->pMemBlock)
		{
			if (tempNode->pMemBlock + tempNode->m_numberOfBytres == nextNode->pMemBlock)
			{
				tempNode->m_numberOfBytres = tempNode->m_numberOfBytres + nextNode->m_numberOfBytres;
				tempNode->m_nextNode = nextNode->m_nextNode;
				nextNode->m_numberOfBytres = 0;
				nextNode->pMemBlock = nullptr;
				nextNode->m_nextNode = nullptr;
				addToEndOfFreeList(nextNode);
			}
			else
			{
				tempNode = tempNode->m_nextNode;
			}
		}
		else
		{
			i++;
			return;
		}
	}
}

bool HeapManager::checkForSequentialFreeBlocks()
{ 
	MemoryDescriptor* descriptor = listOfFreeNodes;
	int i = 0;
	while (descriptor != nullptr && descriptor->m_nextNode != nullptr)
	{
		if (descriptor->pMemBlock > descriptor->m_nextNode->pMemBlock)
		{
			MessagedAssert(true,"unable store the blocks sequentially check code!");
			return false;
		}
		descriptor = descriptor->m_nextNode;
	}
	return true;
}
void HeapManager::addToEndOfFreeList(MemoryDescriptor* descriptor)
{
	MemoryDescriptor* freeNodes = listOfFreeNodes;
	while (freeNodes && freeNodes->m_nextNode)
	{
		freeNodes = freeNodes->m_nextNode;
	}
	freeNodes->m_nextNode = descriptor;
	descriptor->m_nextNode = nullptr;

}
int HeapManager::sizeOfFreeList()
{
	int count = 0;
	MemoryDescriptor* descriptor = listOfFreeNodes;
	while (descriptor)
	{
		count++;
		descriptor = descriptor->m_nextNode;
	}
	return count;
}
int HeapManager::sizeOfAllocatedList()
{
	int count = 0;
	MemoryDescriptor* descriptor = listOfAllocatedNodes;
	while (descriptor)
	{
		count++;
		descriptor = descriptor->m_nextNode;
	}
	return count;
}


void  HeapManager::addSequentiallyToFreeList(MemoryBlockDescriptor* descriptor)
{
	MessagedAssert(!checkIfDescriptorAlreadyPresentInFreeList(descriptor), "cicular list!");
	MemoryDescriptor* freeNodes = listOfFreeNodes;
	//incase of first node insertion
	if (listOfFreeNodes != nullptr )
	{
		if (listOfFreeNodes->pMemBlock && listOfFreeNodes->pMemBlock > descriptor->pMemBlock)
		{
			descriptor->m_nextNode = listOfFreeNodes;
			listOfFreeNodes = descriptor;
			return;
		}
		else if (listOfFreeNodes->pMemBlock == nullptr)
		{
			descriptor->m_nextNode = listOfFreeNodes;
			listOfFreeNodes = descriptor;
			return;
		}
	}
	else
	{
		listOfFreeNodes = descriptor;
		descriptor->m_nextNode = nullptr;
		return;
	}
	while (freeNodes && freeNodes->m_nextNode != nullptr)
	{
		if (freeNodes->pMemBlock && freeNodes->m_nextNode->pMemBlock)
		{
			if (freeNodes->pMemBlock < descriptor->pMemBlock && freeNodes->m_nextNode->pMemBlock > descriptor->pMemBlock)
			{
				MemoryDescriptor* pNextNode = freeNodes->m_nextNode;
				freeNodes->m_nextNode = descriptor;
				descriptor->m_nextNode = pNextNode;
				return;
			}
		}
		 if (freeNodes->m_nextNode->pMemBlock == nullptr)
		{
			MemoryDescriptor* pNextNode = freeNodes->m_nextNode;
			freeNodes->m_nextNode = descriptor;
			descriptor->m_nextNode = pNextNode;
			return;
		}
		freeNodes = freeNodes->m_nextNode;
	}
	freeNodes->m_nextNode = descriptor;
	descriptor->m_nextNode = nullptr;
}

void HeapManager::removeNodeFromAllocatedList(MemoryDescriptor* descriptor)
{
	MemoryDescriptor* allocatedNodes = listOfAllocatedNodes;
	if (listOfAllocatedNodes == nullptr)
	{
		return;
	}
	if (listOfAllocatedNodes == descriptor)
	{
		listOfAllocatedNodes = descriptor->m_nextNode;
	}
	else
	{
		while (allocatedNodes->m_nextNode != descriptor)
		{
			allocatedNodes = allocatedNodes->m_nextNode;
		}

		MemoryDescriptor* swapNode = allocatedNodes->m_nextNode->m_nextNode;
		allocatedNodes->m_nextNode = swapNode;

	}
}

void HeapManager::deleteHeap()
{
	if (memoryBlock)
	_aligned_free(memoryBlock);
	manager->~HeapManager();
	std::free(manager);
	manager = nullptr;

}
void* HeapManager::getFreeDescriptor()
{
	MemoryBlockDescriptor* descripors = listOfFreeNodes;
	while (descripors)
	{
		if (descripors->pMemBlock == nullptr && descripors->m_numberOfBytres == 0)
		{
			return  descripors;
		}
		descripors = descripors->m_nextNode;
	}
	return descripors;
}

void HeapManager::removeNodeFromFreeList(MemoryDescriptor* descriptor)
{
	MemoryDescriptor* freeNodes = listOfFreeNodes;
	if (freeNodes == descriptor)
	{
		MemoryDescriptor* swapNode = freeNodes->m_nextNode;
		if (swapNode)
		{
			freeNodes->m_nextNode = swapNode->m_nextNode;
			listOfFreeNodes = swapNode;
		}
		else
		{
			listOfFreeNodes = nullptr;
		}
	}
	else
	{
		while (freeNodes->m_nextNode != descriptor)
		{
			freeNodes = freeNodes->m_nextNode;
		}
		MemoryDescriptor* swapNode = freeNodes->m_nextNode->m_nextNode;
		freeNodes->m_nextNode = swapNode;

	}
}

	

HeapManager::~HeapManager()
{

}