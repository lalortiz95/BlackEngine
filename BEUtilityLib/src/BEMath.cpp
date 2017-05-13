#include "BEStdHeaders.h"
#include "BEMath.h"
#include "Degree.h"
#include "Radian.h"

namespace BlackEngine
{
	const float Math::PI = std::atanf(1) * 4;
	const float Math::HALF_PI = Math::PI / 2;
	const float Math::QUARTER_PI = Math::HALF_PI / 2;
	const float Math::EULER = 2.71828f;
	const float Math::DELTA = 0.1f;

	Radian Math::Sqrt(const Radian & value)
	{
		return value * value;
	}

	Degree Math::Sqrt(const Degree & value)
	{
		return value * value;
	}

	//static Radian ACos(float value)
	//{
	//	Radian r;
	//	r = std::acos(value);
	//	return r;
	//}

	//static Radian ASin(float value)
	//{
	//	Radian r;
	//	std::asin(value);
	//	return r;
	//}

	//static Radian ATan(float Value)
	//{
	//	std::atan(Value);
	//}

	//static Radian ATan2(float Y, float X)
	//{
	//	std::atan2(Y, X);
	//}
}