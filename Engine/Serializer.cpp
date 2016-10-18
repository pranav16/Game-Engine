#include "Serializer.h"
#include "Assert.h"
#include <fstream>
#include "Vector.h"
namespace Engine
{
	Serializer* Serializer::instance = nullptr;

	Serializer::Serializer()
	{
		serializationBuffer = nullptr;
	}


	Serializer::~Serializer()
	{
		
	}
	void Serializer::shutDown()
	{
		free(startMarker);
		delete instance;
	}
	Serializer* Serializer::getInstance()
	{
		if (instance == nullptr) instance = new Serializer();

		return instance;
	}
	void Serializer::addSerializableObject(Serializable* object)
	{
		MessagedAssert(object != nullptr, "adding null to list of serializble")
		listOfSerializableObjecs.push_back(object);
	}

	void Serializer::serializeObjects()
	{
		MessagedAssert(serializationBuffer != nullptr,"initialize Before Using")
		for (size_t i = 0; i < listOfSerializableObjecs.size(); i++)
		{
		    uint32_t id = static_cast<uint32_t>(listOfSerializableObjecs[i]->getSerializableId().Get());
			memcpy(serializationBuffer,&id, sizeof(uint32_t));
			serializationBuffer += sizeof(uint32_t);
			
			uint32_t type = static_cast<uint32_t>(listOfSerializableObjecs[i]->getSerializableType().Get());
			memcpy(serializationBuffer, &type, sizeof(uint32_t));
			serializationBuffer += sizeof(uint32_t);

			uint8_t* sizeMarker = serializationBuffer;
			memset(serializationBuffer, 0, sizeof(size_t));
			serializationBuffer += sizeof(size_t);
			
			size_t size = listOfSerializableObjecs[i]->serialize(serializationBuffer);
			memset(sizeMarker,size, sizeof(size_t));
			serializationBuffer += size;
		

			MessagedAssert(serializationBuffer < bufferEndMarker, "writing past buffer size");


		}
    	std::ofstream outfile("data\\SaveData.txt", std::ofstream::binary);
		outfile.write(reinterpret_cast<char*>(startMarker), sizeOfBuffer);
		outfile.close();

	}

	bool Serializer::initialize(size_t bufferSize)
	{
		serializationBuffer = reinterpret_cast<uint8_t*>( malloc(bufferSize));
		startMarker = serializationBuffer;
		bufferEndMarker = serializationBuffer + bufferSize;
		sizeOfBuffer = bufferSize;
		return true;
	}

	void Serializer::deSerializeObjects()
	{
		std::ifstream infile("data\\SaveData.txt", std::ifstream::binary);
		if (infile)
		{
			// get length of file:
			infile.seekg(0, infile.end);
			long fileSize = infile.tellg();
			infile.seekg(0, infile.beg);
			assert(serializationBuffer != NULL);
			infile.read(reinterpret_cast<char*>(startMarker), fileSize);
			serializationBuffer = startMarker;
			serializationBuffer = reinterpret_cast<uint8_t*>(serializationBuffer);
			for (size_t i = 0; i < listOfSerializableObjecs.size(); i++)
			{
				uint32_t hashedId;
				memcpy(&(hashedId), serializationBuffer, sizeof(uint32_t));
				uint32_t id = static_cast <uint32_t>(listOfSerializableObjecs[i]->getSerializableId().Get());
				if (id == hashedId)
				{
					//skipping data that we dont need
					serializationBuffer += sizeof(uint32_t);
					serializationBuffer += sizeof(uint32_t);
					serializationBuffer += sizeof(size_t);	
					size_t size = listOfSerializableObjecs[i]->deserialize(serializationBuffer);
					serializationBuffer += size;

				}
			}
		}
		infile.close();
	}
}