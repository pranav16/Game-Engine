#pragma once
namespace Engine
{

		inline Vector4 operator*(const Matrix4 & i_mtx, const Vector4 & i_vec)
		{
			return i_mtx.MultiplyRight(i_vec);
		}

	
		inline Vector4 operator*(const Vector4 & i_vec, const Matrix4 & i_mtx)
		{
			return i_mtx.MultiplyLeft(i_vec);
		}

		inline Vector Matrix4::TransformPointCV(const Vector & i_point) const
		{
			Vector4 Point = MultiplyRight(Vector4(i_point, 1.0f));
			float inv_w = 1.0f / Point.getW();
			return Vector(Point.getX() * inv_w, Point.getY() * inv_w, Point.getZ() * inv_w);
		}

		inline Vector Matrix4::TransformPointRV(const Vector & i_point) const
		{
			Vector4 Point = MultiplyLeft(Vector4(i_point, 1.0f));
			float inv_w = 1.0f / Point.getW();
			return Vector(Point.getX() * inv_w, Point.getY() * inv_w, Point.getZ() * inv_w);
		}

		inline Vector Matrix4::TransformNormalCV(const Vector & i_point) const
		{
			Vector4 Point = MultiplyRight(Vector4(i_point, 0.0f));
			return Vector(Point.getX(), Point.getY(), Point.getZ());
		}

		inline Vector Matrix4::TransformNormalRV(const Vector & i_point) const
		{
			Vector4 Point = MultiplyLeft(Vector4(i_point, 0.0f));
			return Vector(Point.getX(), Point.getY(), Point.getZ());
		}

		inline void Matrix4::Invert(void)
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			InverseSSE(*this);
		}

		inline Matrix4 Matrix4::GetInverse(void) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")

			Matrix4	Temporary(*this);

			InverseSSE(Temporary);

			return Matrix4(Temporary);
		}

		inline void Matrix4::GetInverse(Matrix4 & o_out) const
		{
			InverseSSE(o_out);
		}

		inline Matrix4 Matrix4::operator*(const Matrix4 & i_other) const
		{
			MessagedAssert(!Engine::isNAN(m_11), "matrix is not set up")
#if defined(_WIN32)
			
			if ((reinterpret_cast<uintptr_t>(&i_other) & (16 - 1)) == 0)
			{
				FastMatrix4 tResult;
				MultiplySSE(i_other, tResult);

				return Matrix4(tResult);
			}
#endif

			Matrix4 tResult;
			Multiply(i_other, tResult);

			return Matrix4(tResult);
		}

		inline Matrix4 Matrix4::CreateTranslationCV(const Vector & i_trans)
		{
			return CreateTranslationCV((float)i_trans.getPositionX(), (float)i_trans.getPositionY(), (float)i_trans.getPositionZ());
		}

		inline Matrix4 Matrix4::CreateTranslationRV(const Vector & i_trans)
		{
			return CreateTranslationRV((float)i_trans.getPositionX(), (float)i_trans.getPositionY(), (float)i_trans.getPositionZ());
		}


} // namespace Engine
