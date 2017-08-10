#include <BEPrerequisitesUtility.h>

//#include "BEMathUnitTest.h"
#include <BEMath.h>
#include <Vector3D.h>
#include <BETime.h>
#include <Matrix3D.h>
#include <Quaternion.h>

using namespace BlackEngine;

int main()
{
	BlackEngine::BETime timer;
	float delta;

	timer.SetStartTime();
	BlackEngine::Vector3D vect3;
	///suma
	BE_ASSERT(Math::Sum(5, 5) == 10);
	///resta
	BE_ASSERT(Math::Substraction(5, 5) == 0);
	///multiplicación.
	BE_ASSERT(Math::Multiplication(3, 3) == 9);
	///valor de PI.
	BE_ASSERT((Math::PI - 3.14159f) <= Math::DELTA);
	///coseno con 2 PI (360)
	BE_ASSERT(Math::Cos(Math::PI * 2) == 1);
	///seno de pi
	BE_ASSERT((Math::Sin(Math::PI)) <= Math::DELTA);
	///un número al cuadrado
	BE_ASSERT(Math::Square(3) == 9);
	///exponente de 55 = 4
	//BE_ASSERT(std::fabsf((Math::Loge(55) - 4)) <= Math::DELTA);
	///raiz cuadrada
	BE_ASSERT(Math::Sqrt(9) == 3);
	///tangente.
	BE_ASSERT((Math::Tan(Math::PI)) <= Math::DELTA);
	///redondeo de flotantes
	BE_ASSERT(Math::Trunc(4.5f) == 4);
	BE_ASSERT(Math::Floor(4.5f) == 4);
	BE_ASSERT(Math::Round(4.5f) == 5);
	BE_ASSERT(Math::Ceil(4.5f) == 5);
	///max
	BE_ASSERT(Math::Max(5, 2) == 5);
	///mmin 
	BE_ASSERT(Math::Min(5, 2) == 2);

	///funcionalidad del vector 3D
	vect3.CreateVector({ 20, 20, 20 }, { 5, 5, 5 });
	BE_ASSERT(vect3 == 15);
	timer.SetEndTime();
	delta = timer.ConvertToSeconds();

	Matrix3D M =
	{
		1.0f, -1.0f, 2.0f,
		-2.0f, 0.0f, 4.0f,
		0.0f, -2.0f, 7.0f
	};
	Matrix3D InverseM = M;
	InverseM.Inverse();
	Matrix3D X = M * InverseM;
	BE_ASSERT(M * InverseM == M.Identity());

	//TODO: testear normalización de quaterniones, y su rotación.
	// Multiplicación.
	Quaternion q(28.f, 8.f, 14.8f, 33.8f);
	Quaternion r(16.f, 32.f, 9.f, 60.f);
	Quaternion ExpectedResult(1819.20f, 1546.40f, 1960.19995f, 1190.80f);

	Quaternion multipliedQuaternion = q * r;
	BE_ASSERT(multipliedQuaternion.Equal(ExpectedResult));

	// Suma
	q.Set(2, 3, 4, 5);
	r.Set(2, 3, 4, 5);
	Quaternion addedQuaternion = q + r;
	ExpectedResult.Set(4, 6, 8, 10);
	BE_ASSERT(addedQuaternion.Equal(ExpectedResult));

	// Resta
	q.Set(2, 3, 4, 5);
	r.Set(5, 4, 3, 2);
	Quaternion substractedQuaternion = q - r;
	ExpectedResult.Set(-3, -1, 1, 3);
	BE_ASSERT(substractedQuaternion.Equal(ExpectedResult));



	return 0;
}