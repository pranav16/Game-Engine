#include "StringPool.h"
#include "Assert.h"
#include <string>
namespace Engine
{


StringPool * StringPool::instance = nullptr;
StringPool::StringPool( size_t size)
{
	m_pStartMarker = new uint8_t();
	m_pEndMarker = m_pStartMarker + size;
	m_pEndStrings = m_pStartMarker;

}
StringPool* StringPool::create(size_t maxSize)
{
	MessagedAssert(instance ==nullptr,"recreating string pool!");
	if (instance == nullptr)
	{
		instance = new StringPool(maxSize);
	}
	return instance;
}

const char* StringPool::add(const char* i_pString)
{
	MessagedAssert(i_pString != nullptr, "checking for null string");
	if (find(i_pString) != nullptr)
		return find(i_pString);
	size_t pNewEndString =  strLength(i_pString) + sizeof(size_t);

	MessagedAssert(m_pEndStrings + pNewEndString < m_pEndMarker, "out of storage create a bigger string");
	size_t* size = reinterpret_cast<size_t*>(m_pEndStrings);
	*size = strLength(i_pString);
	m_pEndStrings += sizeof(size_t);
	char* pWord = reinterpret_cast< char*> (m_pEndStrings);
	for (size_t i = 0; i < strLength(i_pString); i++)
	{
		pWord[i] = i_pString[i];
	}
	
	m_pEndStrings += strLength(i_pString);

	return pWord;
}
const char* StringPool::find(const char* i_pString) const
{
	uint8_t* pItr = m_pStartMarker;
	char* pString = nullptr;
	while (pItr < m_pEndStrings && pItr <m_pEndMarker)
	{
		size_t size = (*pItr);
		if (size != strLength(i_pString))
		{
			pItr += size + sizeof(size_t);
			continue;
		}
		uint8_t* pWord = pItr + sizeof(size_t);
		char* pcWord = reinterpret_cast< char*>(pWord);
		if (memcmp(i_pString, pcWord, size) == 0) return pcWord;
		
		pItr += size + sizeof(size_t); 

		
	}
	return pString;
}

StringPool::~StringPool() {

}
}