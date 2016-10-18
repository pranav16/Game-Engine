#ifndef _SMART_POINTER_H
#define _SMART_POINTER_H
#include "Assert.h"
#include "Allocators.h"
namespace Engine
{
	template<class T>
	class SmartPointer
	{
	private:
		T* objectPointedTo;
		long  *  refCount;

	public:
		SmartPointer(T* object)
		{ 
			if (object == nullptr)
			{
				objectPointedTo = nullptr;
				refCount = nullptr;
			}
			else
			{
				objectPointedTo = object;
				refCount = new long(1);
			}
		};		

		SmartPointer()
		{
			objectPointedTo = nullptr;
			refCount = nullptr;
		}
		//use in worse case
		T* getObject()
		{
			return objectPointedTo;
		}
		
		~SmartPointer()
		{	
			MessagedAssert(refCount > 0, "refrence count less that zero");
			if (refCount == nullptr && objectPointedTo == nullptr)
				return;
			(*refCount) -= 1;
			if (*refCount == 0)
			{
				
				delete objectPointedTo;
				delete refCount;
			}
		};
		SmartPointer(const SmartPointer & i_ptr)
		{
			if (i_ptr.refCount == nullptr)
			{
				refCount = nullptr;
				objectPointedTo = nullptr;
				return;
			}
			refCount = i_ptr.refCount;
			(*refCount)++;
			objectPointedTo = i_ptr.objectPointedTo;
		}
		void releaseCurrentObject()
		{
			(*refCount)--;
			if ((*refCount) == 0)
			{
				delete objectPointedTo;
				delete refCount;
			}

		}

		SmartPointer& operator=(const SmartPointer& i_ptr)
		{
			if (this == &i_ptr)
			{
				return *this;
			}
			if (i_ptr.refCount == nullptr)
			{
				refCount = nullptr;
				objectPointedTo = nullptr;
				return *this;
			}
			if(objectPointedTo != nullptr && refCount !=nullptr)
			releaseCurrentObject();
			refCount = i_ptr.refCount;
			(*refCount)++;
			objectPointedTo = i_ptr.objectPointedTo;
			return *this;
		}
	
		inline bool operator==(T*  i_ptr2) const
		{
			return objectPointedTo == i_ptr2 ? true : false;
		}
		inline bool operator==(const SmartPointer & i_ptr1) const
		{
			return objectPointedTo == i_ptr1.objectPointedTo ? true : false;
		}
		inline bool operator!=(const SmartPointer & i_ptr1) const
		{
			return (objectPointedTo != i_ptr2.objectPointedTo) ? true : false;
		}
		inline bool operator!=( T* i_ptr2) const
		{
			return (objectPointedTo != i_ptr2) ? true : false;
		}
		inline T* operator->() const
		{
			MessagedAssert(objectPointedTo != nullptr, "derefrencing a nullptr");
			return objectPointedTo;
		}
		inline T& operator*() const
		{
			MessagedAssert(objectPointedTo != nullptr, "derefrencing a nullptr");
			return (*objectPointedTo);
		}

	};
}

#endif