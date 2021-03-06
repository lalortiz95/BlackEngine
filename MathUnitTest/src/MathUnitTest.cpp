//#include "BEMathUnitTest.h"
//#include <iostream>
//
//using namespace BlackEngine;
//
//void CMathUnitTest::MathUnitTest()
//{
//	BlackEngine::Vector3D vect3;
//	///suma
//	BE_ASSERT(Math::Sum(5, 5) == 10);
//	///resta
//	BE_ASSERT(Math::Substraction(5, 5) == 0);
//	///multiplicación.
//	BE_ASSERT(Math::Multiplication(3, 3) == 9);
//	///valor de PI.
//	BE_ASSERT((Math::PI - 3.14159f) <= Math::DELTA);
//	///coseno con 2 PI (360)
//	BE_ASSERT(Math::Cos(Math::PI * 2) == 1);
//	///seno de pi
//	BE_ASSERT((Math::Sin(Math::PI)) <= Math::DELTA);
//	///un número al cuadrado
//	BE_ASSERT(Math::Square(3) == 9);
//	///exponente de 55 = 4
//	BE_ASSERT((Math::Loge(55) - 4) <= Math::DELTA);
//	///raiz cuadrada
//	BE_ASSERT(Math::Sqrt(9) == 3);
//	///tangente.
//	BE_ASSERT((Math::Tan(Math::PI)) <= Math::DELTA);
//	///redondeo de flotantes
//	BE_ASSERT(Math::Trunc(4.5f) == 4);
//	BE_ASSERT(Math::Floor(4.5f) == 4);
//	BE_ASSERT(Math::Round(4.5f) == 5);
//	BE_ASSERT(Math::Ceil(4.5f) == 5);
//	///max
//	BE_ASSERT(Math::Max(5, 2) == 5);
//	///mmin 
//	BE_ASSERT(Math::Min(5, 2) == 2);
//
//	//Matrix3D M1, M2, Result;
//	//memset(&M1, 6, 9);
//	//memset(&M2, 8, 9);
//	//memset(&Result, 144, 9);
//
//	//BE_ASSERT(M1*M2 == Result);
//
//	///funcionalidad del vector 3D
//	vect3.CreateVector({ 20, 20, 20 }, { 5, 5, 5 });
//	BE_ASSERT(vect3 == 15);
//}