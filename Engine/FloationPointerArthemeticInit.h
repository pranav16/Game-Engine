namespace Engine
{

	inline bool isNAN(const double number)
	{
		const double copy = number;
		return !floatCompareEquals(copy, number);
	
	}

	inline bool floatCompareEquals(const double number1, const double number2, const double epislon)
	{
		if (isNAN(number1) && isNAN(number2))
			return false;
	 
		double diff = number1 - number2;
		
		return (diff < epislon) && (-diff < epislon);


	}

	inline bool floatCompareEquals(const double number1, const double number2)
	{
		const double epislon = 0.0001;
	
		double diff = number1 - number2;

		return (diff < epislon) && (-diff < epislon);

	}

}