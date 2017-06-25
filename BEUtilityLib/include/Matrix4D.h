#pragma once
#include "Matrix3D.h"
#include "Vector4D.h"

namespace BlackEngine
{
	///matrix 4D class
	class BE_UTILITY_EXPORT Matrix4D
	{
	public:
		///union struct, that stores matrix.
		union
		{
			struct
			{
				float m00, m01, m02, m03,
					  m10, m11, m12, m13,
					  m20, m21, m22, m23,
					  m30, m31, m32, m33;
			}_m;
			///bidimensional array to access the matrix.
			float m[4][4];
			///array to access de matrix.
			float _v[16];
		};
		///constructor and destructor
		Matrix4D() {}
		Matrix4D(float X0, float Y0, float Z0, float W0, 
				 float X1, float Y1, float Z1, float W1, 
				 float X2, float Y2, float Z2, float W2,
				 float X3, float Y3, float Z3, float W3 );
		~Matrix4D();

		///inicializa en 0 todos los valores de la matriz.
		Matrix4D Zero();
		///identidad de la matriz
		Matrix4D Identity();

		Matrix4D LookAtLH(Vector4D eye, Vector4D focus, Vector4D up);

		Matrix4D LookToLH(Vector4D EyePosition, Vector4D EyeDirection, Vector4D UpDirection);

		Matrix4D PerspectiveFOVLH(float FOVangle, int width, int height,/*float aspect,*/ float nearZ, float farZ);

		Matrix4D Translate(const Vector4D &position);

		Matrix4D Scale(const Vector4D& scale);

		Matrix4D Rotate(const Vector4D& angles);

		Matrix4D RotateX(float angle);
		Matrix4D RotateY(float angle);
		Matrix4D RotateZ(float angle);


		///realiza la transpuesta de la matriz.
		Matrix4D& Transpose();
		Matrix4D Transpose(Matrix4D M);

		///operadores aritmeticos.
		Matrix4D operator* (Matrix4D M);
		Vector4D operator* (Vector4D V);
		Matrix4D& operator*= (Matrix4D& M) { return *this = *this * M; }

		Matrix4D operator+ (Matrix4D M);
		Matrix4D operator+ (Vector4D V);
		Matrix4D operator+= (Matrix4D& M) { return *this = *this + M; }

		Matrix4D operator- (Matrix4D M);
		Matrix4D operator- (Vector4D V);
		Matrix4D operator-= (Matrix4D& M) { return *this = *this - M; }
	};
}
