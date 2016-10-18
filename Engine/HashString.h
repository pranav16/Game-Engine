#ifndef __HASHED_STRING_H
#define __HASHED_STRING_H

namespace Engine
{

	class HashString
	{
	public:
		HashString();
		~HashString();

		HashString(const char * i_string);
		HashString(const HashString & i_other);
		HashString & operator=(const HashString & i_other);

		unsigned int Get() const;

		bool operator==(const HashString & i_other) const;

		static unsigned int Hash(const char * i_string);
		static unsigned int Hash(const void * i_bytes, unsigned int i_count);
	private:
		 unsigned int 	m_Hash;


	};

}

#include "HashStringIni.h"

#endif 