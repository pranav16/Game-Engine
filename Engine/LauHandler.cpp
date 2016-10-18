#include "LauHandler.h"
#include "Assert.h"
namespace Engine
{

	namespace LauHandler
	{
		int GetLuaTableEntries(lua_State * i_pState, int i_index)
		{
			MessagedAssert(i_pState != nullptr, "nullptr for state in GetLauTableEntries");
			MessagedAssert(lua_gettop(i_pState) >= -i_index, "outofbounds index in GetLauTableEntries ");
			MessagedAssert(lua_type(i_pState, i_index) == LUA_TTABLE, "Type of object is not a table in GetLauTableEntries");

			lua_len(i_pState, i_index);
			MessagedAssert(lua_type(i_pState, -1) != LUA_TNUMBER, "Length is not a number in GetLauTableEntries");

			lua_Integer table_entries = lua_tointeger(i_pState, -1);
			lua_pop(i_pState, 1);

			MessagedAssert(table_entries > INT_MAX, "");

			return static_cast<int>(table_entries);
		}

		size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts)
		{
			MessagedAssert(i_pState != nullptr, "nullptr for state in ReadIntArray");
			MessagedAssert(lua_gettop(i_pState) >= -i_index, "outofbounds index in ReadIntArray ");
			MessagedAssert(lua_type(i_pState, i_index) == LUA_TTABLE, "Type of object is not a table in ReadIntArray");

			size_t	index = 0;

			lua_pushnil(i_pState);

			while (lua_next(i_pState, i_index - 1) != 0)
			{
				if (lua_type(i_pState, -1) == LUA_TNUMBER)
				{
					lua_Integer lValue = lua_tointeger(i_pState, -1);
					MessagedAssert(lValue > INT_MAX, "the integer returned is greater that max int on this system");

					o_pInts[index] = lValue < INT_MAX ? int(lValue) : INT_MAX;
				}
				else
				{
					// DEBUG_PRINT( "Expected a number at position %d while reading table as int array.\n", index );
				}

				lua_pop(i_pState, 1);

				if (++index == i_numInts)
				{
					lua_pop(i_pState, 1);
					break;
				}
			}

			return index;
		}

		size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
		{
			MessagedAssert(i_pState != nullptr, "nullptr for state in ReadFloatArray");
			MessagedAssert(lua_gettop(i_pState) >= -i_index, "outofbounds index in ReadFloatArray ");
			MessagedAssert(lua_type(i_pState, i_index) == LUA_TTABLE, "Type of object is not a table in ReadFloatArray");

			size_t				index = 0;

			lua_pushnil(i_pState);

			while (lua_next(i_pState, i_index - 1) != 0)
			{
				if (lua_type(i_pState, -1) == LUA_TNUMBER)
				{
					o_pFloats[index] = float(lua_tonumber(i_pState, -1));
				}
				else
				{
					// DEBUG_PRINT( "Expected a number at position %d while reading table as float array.\n", index );
				}

				// pop the value now that we've retrieved it
				lua_pop(i_pState, 1);
				if (++index == i_numFloats)
				{
					lua_pop(i_pState, 1);
					break;
				}
			}
			return index;
		}

		size_t GetFloatArray(lua_State * i_pState, int i_indexTable, const char * i_pArrayKey, float * o_pFloats, size_t i_numFloats)
		{
			MessagedAssert(i_pArrayKey != nullptr, "nullptr for arraykey in GetFloatArray");
			MessagedAssert(i_pState != nullptr, "nullptr for state in GetFloatArray");
			lua_pushstring(i_pState, i_pArrayKey);
			i_indexTable--;

			int type = lua_gettable(i_pState, i_indexTable);

			size_t itemsRead = 0;

			if (type == LUA_TTABLE)
				itemsRead = ReadFloatArray(i_pState, i_indexTable, o_pFloats, i_numFloats);
			else
			{
				// DEBUG_PRINT( "Expected Lua table for %s found value of type %d.\n", i_pArrayKey, type );
			}

			lua_pop(i_pState, 1);

			return itemsRead;
		}

		Vector GetVector3(lua_State * i_pState, int i_index)
		{
			MessagedAssert(i_pState != nullptr, "nullptr for state in GetVector3");
			MessagedAssert(lua_gettop(i_pState) >= -i_index, "outofbounds index in GetVector3 ");
			MessagedAssert(lua_type(i_pState, i_index) == LUA_TTABLE, "Type of object is not a table in GetVector3");


			const size_t		numFloats = 3;
			float				v[numFloats] = { 0 };

			size_t	readFloats = ReadFloatArray(i_pState, i_index, v, numFloats);

			return Vector(v[0], v[1], v[2]);
		}


		uint8_t* LoadFile(const char * i_pFilename, size_t & o_sizeFile)
		{
			MessagedAssert(i_pFilename != nullptr, "filepath cannot be null");
			FILE * pFile = NULL;
			errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
			if (fopenError != 0)
				return NULL;
			MessagedAssert(pFile != NULL, "file could not be opened");
			int FileIOError = fseek(pFile, 0, SEEK_END);
			MessagedAssert(FileIOError == 0, "FileIOError");
			long FileSize = ftell(pFile);
			MessagedAssert(FileSize >= 0, "Filesize is less that zero");
			FileIOError = fseek(pFile, 0, SEEK_SET);
			MessagedAssert(FileIOError == 0, "FileIOError");
			uint8_t * pBuffer = new uint8_t[FileSize];
			MessagedAssert(pBuffer != nullptr, "buffer could not be created");
			size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
			MessagedAssert(FileRead == FileSize, "Filesize read is not equal to filesize");
			fclose(pFile);
			o_sizeFile = FileSize;
			return pBuffer;
		}

	}// namespace lauhandler



}//namespace engine