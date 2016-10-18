#pragma once
#ifndef  SERIALIZABLE
#define SERIALIZABLE
#include "HashString.h"
#include <inttypes.h>
namespace Engine
{
class Serializable 
{
public:
	virtual HashString getSerializableType() = 0;
	virtual HashString getSerializableId() = 0;

	virtual size_t serialize(uint8_t* buffer) = 0;
	virtual size_t deserialize(uint8_t* buffer) = 0;

};

}//namespace


#endif // ! SERIALIZABLE
