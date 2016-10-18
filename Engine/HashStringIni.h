#include <assert.h>
#include <string.h>

namespace Engine
{
	inline HashString::HashString() :
		m_Hash(Hash(""))
	{
	}

	inline HashString::HashString(const char * i_string) :
		m_Hash(Hash(i_string))
	{
	}

	inline HashString::HashString(const HashString & i_other) :
		m_Hash(i_other.m_Hash)
	{
	}

	inline HashString::~HashString()
	{

	}

	inline HashString & HashString::operator=(const HashString & i_other)
	{
		m_Hash = i_other.m_Hash;
		return *this;
	}

	inline unsigned int HashString::Get(void) const
	{
		return m_Hash;
	}

	inline bool HashString::operator==(const HashString & i_other) const
	{
		return m_Hash == i_other.m_Hash;
	}

} // namespace Engine
