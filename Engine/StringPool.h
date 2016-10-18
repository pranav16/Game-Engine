#pragma once
#ifndef _STRING_POOL_H
#define _STRING_POOL_H
#include<inttypes.h>
namespace Engine
{

class StringPool
{

public:

	~StringPool();
	static StringPool* create(size_t maxSize);
	inline static StringPool* getInstance();
	const char* add(const char* i_pString);
	const char* find(const char* i_pString) const;

private:
	static StringPool* instance;
	uint8_t*  m_pStartMarker;
	uint8_t* m_pEndMarker;
	uint8_t* m_pEndStrings;
	inline size_t strLength(const char* i_pString) const;
	StringPool(size_t size);
};

}
#include "StringPoolIni.h"
#endif