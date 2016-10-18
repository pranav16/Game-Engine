#pragma once
#include "StringPool.h"
#include <string>
#include "Assert.h"
namespace Engine
{
	size_t StringPool::strLength(const char* i_pString) const
	{
		return std::strlen(i_pString);
	}

	StringPool* StringPool::getInstance()
	{
		MessagedAssert(instance != nullptr, "create string first string pool!");
		return instance;
	}

}