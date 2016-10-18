#ifndef FIXED_SIZE_ALLOCATOR
#define	FIXED_SIZE_ALLOCATOR 
#include <stdint.h>

namespace Engine
{
	class FixedSizeAllocator
	{
	public:
		struct LinkDescriptor
		{
			LinkDescriptor* m_pNext;
		};

		~FixedSizeAllocator();
		void create(void* pMemory, const size_t TotalSize, const size_t blockSize);

		void* alloc();

		bool freeMemory(void* pMemory);
		
		static FixedSizeAllocator* getInstance();

		void deleteHeap();
		
		bool isInRange(uint8_t* blockToCheck) const;
		
		void init();

	private:
		
		FixedSizeAllocator();
		
		static FixedSizeAllocator* instance;
		
		FixedSizeAllocator(const FixedSizeAllocator & allocator){};
		
		const FixedSizeAllocator& operator=(const FixedSizeAllocator& allocator){};
		
		LinkDescriptor* freeList;
		
		void* pMemBlock;

		size_t heapSize;
		
		uint8_t* startMarker;
		
		uint8_t* endMarker;
		
		size_t sizeOfIndividualBlock;
	};
}//namespace
#endif //GuardBands
