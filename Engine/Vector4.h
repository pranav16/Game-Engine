#pragma once
#ifndef VECTOR4_H
#define VECTOR4_H
#include "Vector.h"
namespace Engine
{
	
	class Vector4
	{
	public:
		Vector4() {};
		inline Vector4(float x, float y, float z, float w);
		inline Vector4(const Vector & vector, float w);
		inline Vector4(Vector4 & vector);
		inline float getX() const;
		inline float getY() const;
		inline float getZ() const;
		inline float getW() const;
		
		inline void setX(float x);
		inline void setY(float y);
		inline void setZ(float z);
		inline void setW(float w);

		float Leangth() const;
		float SquareLeangth() const;

		void Normalize();
		Vector4 getUnitVector() const;

		static Vector4 zeroVector;

		inline Vector4& operator=(Vector4& vector);
		inline Vector4& operator+=(Vector4& vector);
		inline Vector4& operator-=(Vector4& vector);
		inline Vector4& operator*=(float factor);
		inline Vector4& operator/=(float factor);
		inline Vector4& operator*(const Vector4 & rhs);

	private:
		float m_x, m_y, m_z, m_w;
		
	};
	inline Vector4 cross(const Vector4 & lhs, const Vector4 & rhs);
	inline Vector4 operator+(const Vector4 & lhs, const Vector4 & rhs);
	inline Vector4 operator-(const Vector4 & lhs, const Vector4 & rhs);

	inline Vector4 operator*(const Vector4 & lhs, float rhs);

	inline Vector4 operator/(const Vector4 & lhs, float rhs);

	inline bool operator==(const Vector4 & lhs, const Vector4 & rhs);
	inline bool operator!=(const Vector4 & lhs, const Vector4 & rhs);

	inline float dot(const Vector4 & lhs, const Vector4 & rhs);
}//namespace Engine
#include "Vector4_Inline.h"
#endif // VECTOR_H
