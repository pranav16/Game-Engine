#ifndef FLOATINGPOINTARTHEMETIC
#define FLOATINGPOINTARTHEMETIC

namespace Engine
{

	inline bool isNAN(const double number);
    
	inline bool floatCompareEquals(const double number1, const double number2, const double epislon);

	inline bool floatCompareEquals(const double number1, const double number2);

}

#include "FloationPointerArthemeticInit.h"

#endif