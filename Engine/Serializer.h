#pragma once
#ifndef  SERIALIZER
#define SERIALIZER

#include "Serializable.h"
#include <inttypes.h>
#include<vector>
namespace Engine
{


	class Serializer
	{
	public:

		~Serializer();
		static Serializer* getInstance();
		void serializeObjects();
		void deSerializeObjects();
		bool initialize(size_t bufferSize);
		void addSerializableObject(Serializable* object);
		void shutDown();
	private:
		
		static Serializer* instance;
		Serializer();
		std::vector<Serializable*> listOfSerializableObjecs;
		uint8_t* serializationBuffer;
		uint8_t* bufferEndMarker;
		uint8_t* startMarker;
		size_t sizeOfBuffer;
	};

}
#endif // ! SERAILIZER
