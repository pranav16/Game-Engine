#ifndef __LAUHANDLER__
#define __LAUHANDLER__
#include "lua.hpp"
#include <inttypes.h>
#include "Vector.h"

namespace Engine
{
	namespace LauHandler
	{
		size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts);
		size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);
		uint8_t* LoadFile(const char * i_pFilename, size_t & o_sizeFile);
		Vector GetVector3(lua_State * i_pState, int i_index);
		
	}
}


#endif