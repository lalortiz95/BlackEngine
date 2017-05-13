#pragma once

#include "BEPrerequisitesUtility.h"
#include "BELogger.h"

namespace BlackEngine
{
	class Radian;
	class Degree;

	class BE_UTILITY_EXPORT Math
	{
	public:
		static const float PI;
		static const float INV_PI;
		static const float HALF_PI;
		static const float QUARTER_PI;
		static const float TWO_PI;
		static const float DELTA;
		static const float EPSILON;

		//TODO: large number, kinda large number, small number, kind of small.

		static const float EULER;

		static const int8_t MIN_INT8;
		static const int16_t MIN_INT16;
		static const int32_t MIN_INT32;
		static const uint8_t MIN_UINT8;
		static const uint16_t MIN_UINT16;
		static const uint32_t MIN_UINT32;

		static const int8_t MAX_INT8;
		static const int16_t MAX_INT16;
		static const int32_t MAX_INT32;
		static const uint8_t MAX_UINT8;
		static const uint16_t MAX_UINT16;
		static const uint32_t MAX_UINT32;

		///redondeos.
		static int Trunc(float F) { return (int)F; }
		static float TruncFloat(float F) { return (float)Trunc(F); }

		///redondeos hacia abajo, arriba, y de .5
		static int Floor(float F) { return Trunc((float)std::floor(F)); }
		static int Round(float F) { return Floor(F + 0.5f); };
		static int Ceil(float F) { return Trunc((float)std::ceil(F)); }

		///suma
		template <typename T>
		static T Sum(T x, T y) { return x + y; }
		///Resta
		template <typename T>
		static T Substraction(T x, T y) { return x - y; }
		///multiplicacion
		template <typename T>
		static T Multiplication(T x, T y) { return x * y; }
		///division
		template <typename T>
		static T Division(T x, T y) { return x / y; }
		///residuo de una division.
		template <typename T>
		static T Residuo(T x, T y) { return x % y; }

		///elevar al cuadrado
		static int Square(int x) { return x * x; }
		///elevar a una potencia deseada.
		template <typename T>
		static T Power(T Num, int Power) { return std::pow(Num, Power); }
		///obtenemos el exponente.
		static float Exp(float value) { return (float)std::exp(value); }
		///factorial de un número.
		static int Factorial(int x)
		{
			int iTemp = 1;
			for (int i = 1; i <= x; i++)
			{
				iTemp *= i;
			}
			return iTemp;
		}

		///funciones logaritmicas
		static float Log2(float value) { return (float)std::log(value); }
		//TODO: arreglar loge declarando LOG2
		static float Loge(float value) { return (float)(std::log(value) /*/ LOG2*/); }
		static float LogX(float base, float value) { return Loge(value) / Loge(base); }

		///funciones para obtener raices.
		static float Sqrt(float value) { return (float)std::sqrt(value); }
		//TODO: arreglar esto creando las variables de tipo Radian y Degree.
		static Radian Sqrt(const Radian& value);
		static Degree Sqrt(const Degree& value);

		///raices cuadradas inversas.
		static float InvSqrt(float F) { return 1.0f / (float)std::sqrt(F); }
		static float InvSqrtEst(float F) { return InvSqrt(F); }

		///funcione que nos indican si tenemos un NAN(not a number), si es infinito, o si es un flotante negativo.
		static bool IsNan(float A) { return ((*(uint32_t*)&A) & 0x7FFFFFFF) > 0x7F800000; }
		static bool IsFinite(float A) { return ((*(uint32_t*)&A) & 0x7F800000) != 0x7F800000; }
		static bool IsNegativeFloat(const float& F1) { return ((*(uint32_t*)&F1) >= (uint32_t)0x80000000); }

		///funciones trigonometricas.
		static float Cos(float Value) { return (float)std::cos(Value); }
		static float Sin(float Value) { return (float)std::sin(Value); }
		static float Tan(float Value) { return (float)std::tan(Value); }

		///funciones trigonometricas con radianes.
		//TODO:implementar estas funciones con radianes ya que esté la clase.

		///funciones de arco coseno, arco seno y arco tangente.
		static Radian ACos(float Value);
		static Radian ASin(float Value);
		//static Radian ATan(float Value) { Radian rad;  std::atan(Value); }
		//static Radian ATan2(float Y, float X) { return(Radian)std::atan2(Value); } ;

		///función que reliza el Lerp
		template <class T, class U>
		static T Lerp(const T& A, const T& B, const U& Alpha)
		{
			return (T)(A + Alpha * (B - A));
		}

		//TODO: SLerp spheric lerp.

		static uint32_t DivideAndRoundUp(uint32_t Dividend, uint32_t Divisor)
		{
			return (Dividend + Divisor - 1) / Divisor;
		}

		///multiplicacion binaria
		static int MulX2(int x) { return x << 1; };
		///division binaria.
		static int DivX2(int x) { return x >> 1; };

		///Regresa el máximo de dos valores
		template< class T >
		static T Max(const T A, const T B)
		{
			return (A >= B) ? A : B;
		}
		///Regresa el mínimo de dos valores
		template< class T >
		static T Min(const T A, const T B)
		{
			return (A <= B) ? A : B;
		}
		///Regresa el máximo de 3 valores
		template< class T >
		static T Max3(const T A, const T B, const T C)
		{
			return Max(Max(A, B), C);
		}
		///Regresa el mínimo de 3 valores
		template< class T >
		static T Min3(const T A, const T B, const T C)
		{
			return Min(Min(A, B), C);
		}

		///función que realiza el clamp.
		template< class T>
		static T Clamp(const T X, const T Min, const T Max)
		{
			return X < Min ? Min : X < Max ? X : Max;
		}
		///variante del clamp en el que debe ser menor a 1 y mayor que 0
		template<typename T>
		static T Clamp01(T val)
		{
			return Max(Min(Val, (T)1), (T)0);
		}

		//TODO: clamp3

		//TODO: no entendí esta madre.
		//template<class T>
		//static T Abs(const T A)
		//{

		//}

		///te regresa el valor de -1, 0 y 1
		template<class T>
		static T Sign(const T A)
		{
			return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
		}
		//TODO: aplicar las funciones de signo para radianes y grados.


	};
}