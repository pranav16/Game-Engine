#include "Vector4.h"

namespace Engine
{


	Vector4 Vector4::zeroVector(0.0, 0.0, 0.0, 0.0);
	Vector4  Vector4::getUnitVector() const
	{
		float length = Leangth();
		if (length == 0.0f)
			return zeroVector;
		float unitFactor = 1.0f / length;
		return *this * unitFactor;
	}

	void  Vector4::Normalize()
	{
		float length = Leangth();
		if (length == 0.0f)
			return;
		float unitFactor = 1.0f / length;
		*this = *this * unitFactor;
	}
	float  Vector4::Leangth() const
	{
		return   sqrt(SquareLeangth());
	}
	float  Vector4::SquareLeangth() const
	{
		return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
	}



}