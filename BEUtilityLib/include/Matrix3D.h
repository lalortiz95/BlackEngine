#pragma once
#include "BEMath.h"
#include "Vector3D.h"

namespace BlackEngine
{
	class BE_UTILITY_EXPORT Matrix3D
	{
	public:
		union
		{
			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			}_m;
			float m[3][3];
			float v[9];
		};
		Matrix3D() {}
		Matrix3D(float X0, float Y0, float Z0,
			float X1, float Y1, float Z1,
			float X2, float Y2, float Z2);
		~Matrix3D();

		///inicializa en 0 todos los valores de la matriz.
		Matrix3D Zero();
		//determinante, inverza.
		//translacion, rotación y escala.

		///realiza la transpuesta de la matriz.
		Matrix3D Transpose(Matrix3D M);

		///identidad de la matriz
		Matrix3D Identity();

		///Inverza de la matriz.
		void Inverse();
		Matrix3D GetAdjunct(Matrix3D M);
		float GetDeterminant(Matrix3D M, int32 col, int32 row);

		///operadores aritmeticos.
		Matrix3D operator* (Matrix3D M);
		Matrix3D operator* (Vector3D V);
		Matrix3D& operator*=(Matrix3D& M) { return *this = *this * M; }

		Matrix3D operator/ (float fVal);
		Matrix3D& operator/=(float fVal) { return *this = *this / fVal; }

		Matrix3D operator+ (Matrix3D M);
		Matrix3D operator+ (Vector3D V);
		Matrix3D operator+= (Matrix3D& M) { return *this = *this + M; }

		Matrix3D operator- (Matrix3D M);
		Matrix3D operator- (Vector3D V);
		Matrix3D operator-= (Matrix3D& M) { return *this = *this - M; }

		bool operator== (Matrix3D M);
	};
}