#pragma once
#include "BEMath.h"
#include "Vector3D.h"

namespace BlackEngine
{
	class Matrix3D
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
		~Matrix3D();

		///inicializa en 0 todos los valores de la matriz.
		Matrix3D Zero();
		//determinante, inverza.
		//translacion, rotación y escala.

		///realiza la transpuesta de la matriz.
		Matrix3D Transpose(Matrix3D M);

		///operadores aritmeticos.
		Matrix3D operator* (Matrix3D M);
		Matrix3D operator* (Vector3D V);
		Matrix3D& operator*=(Matrix3D& M) { return *this = *this * M; }

		Matrix3D operator+ (Matrix3D M);
		Matrix3D operator+ (Vector3D V);
		Matrix3D operator+= (Matrix3D& M) { return *this = *this + M; }

		Matrix3D operator- (Matrix3D M);
		Matrix3D operator- (Vector3D V);
		Matrix3D operator-= (Matrix3D& M) { return *this = *this - M; }

		bool operator== (Matrix3D M);
	};
}