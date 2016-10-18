#ifndef __COORDINATE_H_
#define __COORDINATE_H_
#include <istream>

namespace Engine
{
	class Vector
	{
	public:
		inline Vector() {};
		inline Vector(const Vector& vector) : x(vector.x), y(vector.y), z(vector.z){};
		inline Vector(double x, double y, double z) : x(x), y(y), z(z){};
		~Vector();
		inline void setPostionX(const double x);
		inline void setPostionY(const double y);
		inline void setPositionZ(const double z);
		inline double getPositionX()  const;
		inline double getPositionY()  const;
		inline double getPositionZ()  const;
		inline  Vector& operator=(const Vector &a);
		inline std::string VectorToString() const;
		inline Vector& operator*(const double multiplier);
		inline Vector& operator/(const double divider);
		inline float magnitude();
		static const Vector VectorZero;

	private:
		double x, y, z;
	};
	inline Vector operator+(const Vector &a, const Vector &b);
	inline Vector operator-(const Vector &a, const Vector &b);
	inline Vector& operator+=(Vector &a, const Vector &b);
	inline Vector& operator-=(Vector &a, const Vector &b);
	inline bool operator==(const Vector &a, const Vector &b);
	inline double dot(const Vector &a, const Vector &b);

	
	
		
} //namespace engine.

#include "Vector_Inline.h"
#endif //__COORDINATE_H_