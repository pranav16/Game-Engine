#include "Vector.h"
#include "assert.h"
#include "FloatingPointArthimetic.h"

namespace Engine
{
	
	inline double Vector::getPositionX() const
	{
		return x;
	}
	inline double Vector::getPositionY() const
	{
		return y;
	}
	inline double Vector::getPositionZ() const
	{
		return z;
	}

	inline void Vector::setPostionX(const double x) 
	{
		MessagedAssert(!Engine::isNAN(x), "posistion x can not be NAN");
		this->x = x;
	}
	inline void Vector::setPostionY(const double y)
	{
		MessagedAssert(!Engine::isNAN(y), "posistion y can not be NAN");
		this->y = y;
	}
	inline void Vector::setPositionZ(const double z)
	{
		MessagedAssert(!Engine::isNAN(z), "posistion z can not be NAN");
		this->z = z;
	}
	inline Vector operator+(const Vector &a, const Vector &b)
	{
		Vector C(a.getPositionX()+b.getPositionX(),a.getPositionY()+b.getPositionY(),a.getPositionZ()+b.getPositionZ());
		return C;
	}
	inline Vector operator-(const Vector &a, const Vector &b)
	{
		Vector C(a.getPositionX() - b.getPositionX(), a.getPositionY() - b.getPositionY(), a.getPositionZ() - b.getPositionZ());
		return C;
	}
	inline Vector& operator+=(Vector &a, const Vector &b)
	{
		a.setPostionX(a.getPositionX() + b.getPositionX());
		a.setPostionY(a.getPositionY() + b.getPositionY());
		a.setPositionZ(a.getPositionZ() + b.getPositionZ());
		return a;
	}
	inline Vector& operator-=(Vector &a, const Vector &b)
	{
		a.setPostionX(a.getPositionX() - b.getPositionX());
		a.setPostionY(a.getPositionY() - b.getPositionY());
		a.setPositionZ(a.getPositionZ() - b.getPositionZ());
		return a;
	}
	inline bool operator==(const Vector &a, const Vector &b)
	{

		if (Engine::floatCompareEquals(a.getPositionX(), b.getPositionX()) && Engine::floatCompareEquals(a.getPositionY(), b.getPositionY()) && Engine::floatCompareEquals(a.getPositionZ(), b.getPositionZ()))
			return true;

		return false;

	}
	inline double dot(const Vector &a, const Vector &b)
	{
		return a.getPositionX() * b.getPositionX() + a.getPositionY() * b.getPositionY() + a.getPositionZ() * b.getPositionZ();
	}
	
	inline Vector& Vector::operator=(const Vector &a)
	{
		setPostionX(a.getPositionX());
		setPostionY(a.getPositionY());
		setPositionZ(a.getPositionZ());
		return *this;
	}
	inline std::string Vector::VectorToString() const
	{
		char buff[100];
		sprintf_s(buff,"X:%f Y:%f Z:%f",x,y,z);
		return buff;
	}
	inline Vector& Vector::operator*(const double multiplier)
	{
		setPostionX(getPositionX() *  multiplier);
		setPostionY(getPositionY() *  multiplier);
		setPositionZ(getPositionZ() *  multiplier);

		return *this;
	}
	inline Vector& Vector::operator/(const double divider)
	{
		setPostionX(getPositionX() / divider);
		setPostionY(getPositionY() / divider);
		setPositionZ(getPositionZ() / divider);

		return *this;
	}
	inline float Vector::magnitude()
	{
		return (float)sqrt(x * x + y* y + z* z);
	}
	
} //namespace engine.


