#include "Matrix4.h"
#include <math.h>
#include <stdint.h>
#include "Assert.h"
namespace Engine
{
	

		const FastMatrix4 Matrix4::Identity(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		Matrix4::Matrix4(void)
		{
#ifdef _DEBUG
		
			m_11 = NAN;
#endif
		}

		Matrix4::Matrix4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44)
			:
			m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
			m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
			m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
			m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
		{

		}

		Matrix4::Matrix4(const Matrix4 & i_other)
			:
			m_11(i_other.m_11), m_12(i_other.m_12), m_13(i_other.m_13), m_14(i_other.m_14),
			m_21(i_other.m_21), m_22(i_other.m_22), m_23(i_other.m_23), m_24(i_other.m_24),
			m_31(i_other.m_31), m_32(i_other.m_32), m_33(i_other.m_33), m_34(i_other.m_34),
			m_41(i_other.m_41), m_42(i_other.m_42), m_43(i_other.m_43), m_44(i_other.m_44)
		{

		}

		Matrix4 & Matrix4::operator=(const Matrix4 & i_other)
		{
			m_11 = i_other.m_11; m_12 = i_other.m_12; m_13 = i_other.m_13; m_14 = i_other.m_14;
			m_21 = i_other.m_21; m_22 = i_other.m_22; m_23 = i_other.m_23; m_24 = i_other.m_24;
			m_31 = i_other.m_31; m_32 = i_other.m_32; m_33 = i_other.m_33; m_34 = i_other.m_34;
			m_41 = i_other.m_41; m_42 = i_other.m_42; m_43 = i_other.m_43; m_44 = i_other.m_44;

			return *this;
		}

		void Matrix4::Transpose(void)
		{
			MessagedAssert(!Engine::isNAN(m_11),"matrix is not set up")
			register float temp;
			temp = m_21; m_21 = m_12; m_12 = temp;
			temp = m_31; m_31 = m_13; m_13 = temp;
			temp = m_41; m_41 = m_14; m_14 = temp;

			temp = m_32; m_32 = m_23; m_23 = temp;
			temp = m_42; m_42 = m_24, m_24 = temp;

			temp = m_43; m_43 = m_34; m_34 = temp;
		}

		Matrix4 Matrix4::GetTranspose(void) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			return Matrix4(
				m_11, m_21, m_31, m_41,
				m_12, m_22, m_32, m_42,
				m_13, m_23, m_33, m_43,
				m_14, m_24, m_34, m_44);
		}

		void Matrix4::GetTranspose(Matrix4 & o_out) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			o_out.m_11 = m_11; o_out.m_12 = m_21; o_out.m_13 = m_31; o_out.m_14 = m_41;
			o_out.m_21 = m_12; o_out.m_22 = m_22; o_out.m_23 = m_32; o_out.m_24 = m_42;
			o_out.m_31 = m_13; o_out.m_32 = m_23; o_out.m_33 = m_33; o_out.m_34 = m_43;
			o_out.m_41 = m_14; o_out.m_42 = m_24; o_out.m_43 = m_34; o_out.m_44 = m_44;
		}
		//row major
		Vector4 Matrix4::MultiplyLeft(const Vector4 & i_Vector) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			return Vector4(
				i_Vector.getX() * m_11 + i_Vector.getY() * m_21 + i_Vector.getZ() * m_31 + i_Vector.getW() * m_41,
				i_Vector.getX() * m_12 + i_Vector.getY() * m_22 + i_Vector.getZ() * m_32 + i_Vector.getW() * m_42,
				i_Vector.getX() * m_13 + i_Vector.getY() * m_23 + i_Vector.getZ() * m_33 + i_Vector.getW() * m_43,
				i_Vector.getX() * m_14 + i_Vector.getY() * m_24 + i_Vector.getZ() * m_34 + i_Vector.getW() * m_44);
		}
		//coloum major
		Vector4 Matrix4::MultiplyRight(const Vector4 & i_Vector) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			return Vector4(
				i_Vector.getX() * m_11 + i_Vector.getY() * m_12 + i_Vector.getZ() * m_13 + i_Vector.getW() * m_14,
				i_Vector.getX() * m_21 + i_Vector.getY() * m_22 + i_Vector.getZ() * m_23 + i_Vector.getW() * m_24,
				i_Vector.getX() * m_31 + i_Vector.getY() * m_32 + i_Vector.getZ() * m_33 + i_Vector.getW() * m_34,
				i_Vector.getX() * m_41 + i_Vector.getY() * m_42 + i_Vector.getZ() * m_43 + i_Vector.getW() * m_44);
		}
		//this *  i_other
		void Matrix4::MultiplyInt(const Matrix4 & i_other, Matrix4 & o_out) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")
				MessagedAssert(!Engine::isNAN(i_other.m_11), "matrix is not set up")

			o_out.m_11 = m_11 * i_other.m_11 + m_12 * i_other.m_21 + m_13 * i_other.m_31 + m_14 * i_other.m_41;
			o_out.m_12 = m_11 * i_other.m_12 + m_12 * i_other.m_22 + m_13 * i_other.m_32 + m_14 * i_other.m_42;
			o_out.m_13 = m_11 * i_other.m_13 + m_12 * i_other.m_23 + m_13 * i_other.m_33 + m_14 * i_other.m_43;
			o_out.m_14 = m_11 * i_other.m_14 + m_12 * i_other.m_24 + m_13 * i_other.m_34 + m_14 * i_other.m_44;

			o_out.m_21 = m_21 * i_other.m_11 + m_22 * i_other.m_21 + m_23 * i_other.m_31 + m_24 * i_other.m_41;
			o_out.m_22 = m_21 * i_other.m_12 + m_22 * i_other.m_22 + m_23 * i_other.m_32 + m_24 * i_other.m_42;
			o_out.m_23 = m_21 * i_other.m_13 + m_22 * i_other.m_23 + m_23 * i_other.m_33 + m_24 * i_other.m_43;
			o_out.m_24 = m_21 * i_other.m_14 + m_22 * i_other.m_24 + m_23 * i_other.m_34 + m_24 * i_other.m_44;

			o_out.m_31 = m_31 * i_other.m_11 + m_32 * i_other.m_21 + m_33 * i_other.m_31 + m_34 * i_other.m_41;
			o_out.m_32 = m_31 * i_other.m_12 + m_32 * i_other.m_22 + m_33 * i_other.m_32 + m_34 * i_other.m_42;
			o_out.m_33 = m_31 * i_other.m_13 + m_32 * i_other.m_23 + m_33 * i_other.m_33 + m_34 * i_other.m_43;
			o_out.m_34 = m_31 * i_other.m_14 + m_32 * i_other.m_24 + m_33 * i_other.m_34 + m_34 * i_other.m_44;

			o_out.m_41 = m_41 * i_other.m_11 + m_42 * i_other.m_21 + m_43 * i_other.m_31 + m_44 * i_other.m_41;
			o_out.m_42 = m_41 * i_other.m_12 + m_42 * i_other.m_22 + m_43 * i_other.m_32 + m_44 * i_other.m_42;
			o_out.m_43 = m_41 * i_other.m_13 + m_42 * i_other.m_23 + m_43 * i_other.m_33 + m_44 * i_other.m_43;
			o_out.m_44 = m_41 * i_other.m_14 + m_42 * i_other.m_24 + m_43 * i_other.m_34 + m_44 * i_other.m_44;
		}

		void Matrix4::Multiply(const Matrix4 & i_other, Matrix4 & o_out) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")
			MessagedAssert(!Engine::isNAN(i_other.m_11), "matrix is not set up")

#if defined(_WIN32)
		
			if ((reinterpret_cast<uintptr_t>(&i_other) & (16 - 1)) == 0)
			{
				MultiplySSE(i_other, o_out);
				return;
			}
#endif

			MultiplyInt(i_other, o_out);
		}


		Matrix4 Matrix4::CreateIdentity(void)
		{
			return Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::CreateScale(float i_scaleX, float i_scaleY, float i_scaleZ)
		{
			return Matrix4(
				i_scaleX, 0.0f, 0.0f, 0.0f,
				0.0f, i_scaleY, 0.0f, 0.0f,
				0.0f, 0.0f, i_scaleZ, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::CreateTranslationRV(float i_transX, float i_transY, float i_transZ)
		{
			return Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				i_transX, i_transY, i_transZ, 1.0f);
		}

		Matrix4 Matrix4::CreateXRotationCV(float i_RotationRadians)
		{
			float sin = sinf(i_RotationRadians);
			float cos = cosf(i_RotationRadians);

			return Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos, -sin, 0.0f,
				0.0f, sin, cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::CreateYRotationCV(float i_RotationRadians)
		{
			float sin = sinf(i_RotationRadians);
			float cos = cosf(i_RotationRadians);

			return Matrix4(
				cos, 0.0f, sin, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sin, 0.0f, cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}
		Matrix4 Matrix4::CreateZRotationCV(float i_RotationRadians)
		{
			float sin = sinf(i_RotationRadians);
			float cos = cosf(i_RotationRadians);

			return Matrix4(
				cos, -sin, 0.0f, 0.0f,
				sin, cos, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::CreateTranslationCV(float i_transX, float i_transY, float i_transZ)
		{
			return Matrix4(
				1.0f, 0.0f, 0.0f, i_transX,
				0.0f, 1.0f, 0.0f, i_transY,
				0.0f, 0.0f, 1.0f, i_transZ,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::CreateXRotationRV(float i_RotationRadians)
		{
			float sin = sinf(i_RotationRadians);
			float cos = cosf(i_RotationRadians);

			return Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos, sin, 0.0f,
				0.0f, -sin, cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::CreateYRotationRV(float i_RotationRadians)
		{
			float sin = sinf(i_RotationRadians);
			float cos = cosf(i_RotationRadians);

			return Matrix4(
				cos, 0.0f, -sin, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				sin, 0.0f, cos, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}
		Matrix4 Matrix4::CreateZRotationRV(float i_RotationRadians)
		{
			float sin = sinf(i_RotationRadians);
			float cos = cosf(i_RotationRadians);

			return Matrix4(
				cos, sin, 0.0f, 0.0f,
				-sin, cos, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::GetInverseRotTransCV() const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")


			return Matrix4(
				m_11, m_21, m_31, -((m_11 * m_14) + (m_21 * m_24) + (m_31 * m_34)),
				m_12, m_22, m_32, -((m_12 * m_14) + (m_22 * m_24) + (m_32 * m_34)),
				m_13, m_23, m_33, -((m_13 * m_14) + (m_23 * m_24) + (m_33 * m_34)),
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Vector4 Matrix4::Row(size_t i_row) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			switch (i_row)
			{
			case 0:
				return Vector4(m_11, m_12, m_13, m_14);
			case 1:
				return Vector4(m_21, m_22, m_23, m_24);
			case 2:
				return Vector4(m_31, m_32, m_33, m_34);
			case 3:
				return Vector4(m_41, m_42, m_43, m_44);
			default:
				return Vector4(NAN, NAN, NAN, NAN);
			}
		}

		Vector4 Matrix4::Col(size_t i_col) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			switch (i_col)
			{
			case 0:
				return Vector4(m_11, m_21, m_31, m_41);
			case 1:
				return Vector4(m_12, m_22, m_32, m_42);
			case 2:
				return Vector4(m_13, m_23, m_33, m_43);
			case 3:
				return Vector4(m_14, m_24, m_34, m_44);
			default:
				return Vector4(NAN, NAN, NAN, NAN);
			}
		}

		Matrix4 Matrix4::GetInverseRotTransRV() const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")
			
			return Matrix4(
				m_11, m_21, m_31, 0.0f,
				m_12, m_22, m_32, 0.0f,
				m_13, m_23, m_33, 0.0f,
				-((m_11 * m_41) + (m_12 * m_42) + (m_13 * m_43)), -((m_21 * m_41) + (m_22 * m_42) + (m_23 * m_43)), -((m_31 * m_41) + (m_32 * m_42) + (m_33 * m_43)), 1.0f);
		}


} // namespace Engine