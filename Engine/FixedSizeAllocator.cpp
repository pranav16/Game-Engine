#include "FixedSizeAllocator.h"
#include "assert.h"
#include<algorithm>
namespace Engine
{
	FixedSizeAllocator* FixedSizeAllocator::instance = nullptr;

	FixedSizeAllocator::FixedSizeAllocator()
	{
		pMemBlock = nullptr;
		freeList = nullptr;
		heapSize = 0;
		sizeOfIndividualBlock = 0;
	}

	void FixedSizeAllocator::init()
	{
		pMemBlock = nullptr;
		freeList = nullptr;
		heapSize = 0;
		sizeOfIndividualBlock = 0;
	}

	FixedSizeAllocator::~FixedSizeAllocator()
	{

	}

	void FixedSizeAllocator::deleteHeap()
	{
		if (pMemBlock)
			_aligned_free(pMemBlock);
		instance->~FixedSizeAllocator();
		std::free(instance);
		instance = nullptr;
	}

	void FixedSizeAllocator::create(void* pMemory, const size_t TotalSize, const size_t blockSize)
	{
		MessagedAssert(pMemory != nullptr, "creating heap with null memory");
		MessagedAssert(pMemBlock == nullptr, "reinitializing fixedsizeallocator")
			MessagedAssert(TotalSize % blockSize == 0, "the memory block does not allign well with the block size");
		pMemBlock = pMemory;
		heapSize = TotalSize;
		sizeOfIndividualBlock = blockSize;
		freeList = reinterpret_cast<LinkDescriptor*>(pMemBlock);
		uint8_t* next = reinterpret_cast<uint8_t*> (freeList)+sizeOfIndividualBlock;
		freeList->m_pNext = reinterpret_cast<LinkDescriptor*>(next);
		size_t totalNumberOfBlocks = TotalSize / blockSize;
		LinkDescriptor* tempDesciptor = freeList->m_pNext;

		for (size_t i = 2; i < totalNumberOfBlocks; i++)
		{

			uint8_t* next = reinterpret_cast<uint8_t*> (tempDesciptor)+sizeOfIndividualBlock;
			tempDesciptor->m_pNext = reinterpret_cast<LinkDescriptor*>(next);
			tempDesciptor = tempDesciptor->m_pNext;

		}
		tempDesciptor->m_pNext = nullptr;
		startMarker = reinterpret_cast<uint8_t*> (freeList);
		endMarker = reinterpret_cast<uint8_t*>(freeList)+totalNumberOfBlocks * sizeof(freeList);
	}

	void* FixedSizeAllocator::alloc()
	{
		MessagedAssert(pMemBlock != nullptr, "allocate memory to heap before using it");
		void* blockToReturn = nullptr;
		if (!freeList)
			return blockToReturn;

		blockToReturn = reinterpret_cast<void*>(freeList);
		freeList = freeList->m_pNext;
		return blockToReturn;
	}

	bool FixedSizeAllocator::freeMemory(void* pMemory)
	{
		MessagedAssert(pMemory != nullptr, "trying to free null");
		bool condition = pMemory < startMarker && pMemory > endMarker;
		if (condition)
		{
			MessagedAssert(!condition, "trying to free memory block that was not manged by this heap");
			return false;
		}
		LinkDescriptor* descriptors = freeList;
		freeList = reinterpret_cast<LinkDescriptor*>(pMemory);
		freeList->m_pNext = descriptors;

		return true;
	}

	FixedSizeAllocator* FixedSizeAllocator::getInstance()
	{
		if (instance == nullptr)
		{
			void* memBlock = malloc(sizeof(FixedSizeAllocator));
			instance = new(memBlock)FixedSizeAllocator;


		}
		return instance;
	}

	bool FixedSizeAllocator::isInRange(uint8_t* blockToCheck) const 
	{
		if ( (startMarker < blockToCheck && blockToCheck < endMarker) || (startMarker == blockToCheck) || (blockToCheck == endMarker))
			return true;

		return false;

	}
}