#pragma once
#ifndef  ITYPE_H
#define ITYPE_H
#include "HashString.h"
#include "Assert.h"
namespace Engine
{


	class IType
	{
	public:
		inline IType(const HashString type) :m_type(type) {};

		~IType() { MessagedAssert(false, "") };


		const HashString m_type;

	};

}
#endif // ! ITYPE_H
