
#include "Assert.h"

namespace Engine
{

	inline Vector4::Vector4(float x, float y, float z, float w):m_x(x),m_y(y),m_z(z),m_w(w)
	{
	
	}
	inline Vector4::Vector4(const Vector & vector, float w) : m_x((float)vector.getPositionX()), m_y((float)vector.getPositionY()), m_z((float)vector.getPositionZ()), m_w(w)
	{
		
	}
	inline  Vector4::Vector4(Vector4 & vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w)
	{

	}
	inline float  Vector4::getX() const
	{
		return m_x;
	}
	inline float  Vector4::getY() const
	{
		return m_y;
	}
	inline float  Vector4::getZ() const
	{
		return m_z;
	}
	inline float  Vector4::getW() const
	{
		return m_w;
	}

	inline void  Vector4::setX(float x)
	{
		m_x = x;
	}
	inline void  Vector4::setY(float y)
	{
		m_y = y;
	}
	inline void  Vector4::setZ(float z)
	{
		m_z = z;
	}
	inline void  Vector4::setW(float w)
	{
		m_w = w;
	}
	inline Vector4& Vector4::operator*(const Vector4 & rhs)
	{
		m_x *= rhs.m_x;
		m_y *= rhs.m_y;
		m_z *= rhs.m_z;
		m_w *= rhs.m_w;
		return  *this;
	}


	inline Vector4&  Vector4::operator=(Vector4& vector)
	{
		m_x = vector.m_x;
		m_y = vector.m_y;
		m_z = vector.m_z;
		m_w = vector.m_w;
		return *this;
	}

	inline Vector4&  Vector4::operator+=(Vector4& vector)
	{
		m_x += vector.m_x;
		m_y += vector.m_y;
		m_z += vector.m_z;
		m_w += vector.m_w;
		return *this;
	}
	inline Vector4&  Vector4::operator-=(Vector4& vector)
	{
		m_x -= vector.m_x;
		m_y -= vector.m_y;
		m_z -= vector.m_z;
		m_w -= vector.m_w;
		return *this;
	}
	inline Vector4&  Vector4::operator*=(float factor)
	{
		m_x *= factor;
		m_y *= factor;
		m_z *= factor;
		m_w *= factor;
		return *this;
	}
	inline Vector4&  Vector4::operator/=(float factor)
	{
		m_x /= factor;
		m_y /= factor;
		m_z /= factor;
		m_w /= factor;
		return *this;
	}
	inline Vector4  operator+(const Vector4 & lhs, const Vector4 & rhs)
	{
		return Vector4(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY(), lhs.getZ() + rhs.getZ(), lhs.getW() + rhs.getW());
	}
	inline Vector4  operator-(const Vector4 & lhs, const Vector4 & rhs)
	{
		return Vector4(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ(), lhs.getW() - rhs.getW());
	}

	inline Vector4 operator*(const Vector4 & lhs, float factor)
	{
		return  Vector4(lhs.getX()* factor, lhs.getY()* factor, lhs.getZ()* factor, lhs.getW()* factor);
	}
	inline Vector4 cross(const Vector4 & lhs, const Vector4 & rhs)
	{
		float a = lhs.getX() * rhs.getZ() - lhs.getZ() * rhs.getY();
		float b = lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ();
		float c = lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX();
		
		return Vector4(a, b, c, 1.0f);
	}
	inline Vector4  operator/(const Vector4 & lhs, float factor)
	{
		MessagedAssert(factor != 0.0f, "dividing by zero");
		return  Vector4(lhs.getX() / factor, lhs.getY() / factor, lhs.getZ()/ factor, lhs.getW()/ factor);
	}

	inline bool operator==(const Vector4 & lhs, const Vector4 & rhs)	{
		
	  return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ() && lhs.getW() == rhs.getW();
	}
	inline bool operator!=(const Vector4 & lhs, const Vector4 & rhs)
	{
		return !(lhs == rhs);
	}

	inline float  dot(const Vector4 & lhs, const Vector4 & rhs)
	{
		return lhs.getX() * rhs.getX() + lhs.getY() * rhs.getY() + lhs.getZ() * rhs.getZ() + lhs.getW() * rhs.getW();
	}
}
#ifndef  VECTOR4INLINE
#define	VECTOR4INLINE
#endif // ! VECTOR4INLINE
