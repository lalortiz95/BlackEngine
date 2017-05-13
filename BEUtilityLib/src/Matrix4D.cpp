#include "Matrix4D.h"

namespace BlackEngine
{
	Matrix4D::Matrix4D
	(
		float X0, float Y0, float Z0, float W0,
		float X1, float Y1, float Z1, float W1,
		float X2, float Y2, float Z2, float W2,
		float X3, float Y3, float Z3, float W3
	)
	{
		_m.m00 = X0; _m.m01 = Y0; _m.m02 = Z0; _m.m03 = W0;
		_m.m10 = X1; _m.m11 = Y1; _m.m12 = Z1; _m.m13 = W1;
		_m.m20 = X2; _m.m21 = Y2; _m.m22 = Z2; _m.m23 = W2;
		_m.m30 = X3; _m.m31 = Y3; _m.m32 = Z3; _m.m33 = W3;
	}
	Matrix4D::~Matrix4D()
	{
	}

	Matrix4D Matrix4D::Zero()
	{
		Matrix4D R;
		memset(&R, 0, sizeof(R));
		return R;
	}

	Matrix4D Matrix4D::Identity()
	{
		Matrix4D Identity = Zero();
		Identity._m.m00 = 1;
		Identity._m.m11 = 1;
		Identity._m.m22 = 1;
		Identity._m.m33 = 1;
		return Identity;
	}

	Matrix4D Matrix4D::LookAtLH(Vector4D eyePosition, Vector4D focusPosition, Vector4D upDirection)
	{
		Matrix4D M;
		Vector4D Up;
		Vector4D Right;
		Vector4D Front = focusPosition - eyePosition;
		Front.Normalize();
		Right.CrossProduct(upDirection, Front);
		Right.Normalize();
		Up.CrossProduct(Front, Right);
		Up.Normalize();

		M = M.Zero();
		///row 1:
		M.m[0][0] = Right.X;
		M.m[0][1] = Up.X;
		M.m[0][2] = Front.X;
		M.m[0][3] = 0;
		///row 2:
		M.m[1][0] = Right.Y;
		M.m[1][1] = Up.Y;
		M.m[1][2] = Front.Y;
		M.m[1][3] = 0;
		///row 3:
		M.m[2][0] = Right.Z;
		M.m[2][1] = Up.Z;
		M.m[2][2] = Front.Z;
		M.m[2][3] = 0;
		///row 4:
		M.m[3][0] = Right.DotProduct(eyePosition);
		M.m[3][1] = -Up.DotProduct(eyePosition);
		M.m[3][2] = -Front.DotProduct(eyePosition);
		M.m[3][3] = 1;
		
		return M;
	}

	Matrix4D Matrix4D::LookToLH(Vector4D EyePosition, Vector4D EyeDirection, Vector4D UpDirection)
	{
		Vector4D Right;
		Vector4D Up;
		Vector4D Front = EyeDirection - EyePosition;
		Front.Normalize();
		Right.CrossProduct(UpDirection, Front);
		Right.Normalize();
		Up.CrossProduct(Front, Right);
		Right *= -1;
		Up *= -1;
		Front *= -1;

		Matrix4D M;
		//row 1.				//row 2.
		M._m.m00 = Right.X;		M._m.m10 = Up.X;
		M._m.m01 = Right.Y;		M._m.m11 = Up.Y;
		M._m.m02 = Right.Z;		M._m.m12 = Up.Z;
		M._m.m03 = 0;			M._m.m13 = 0;
		//row 3.				//row 4.
		M._m.m20 = Front.X;		M._m.m30 = 0;
		M._m.m21 = Front.Y;		M._m.m31 = 0;
		M._m.m22 = Front.Z;		M._m.m32 = 0;
		M._m.m23 = 0;			M._m.m33 = 1;

		return M;
	}

	Matrix4D Matrix4D::PerspectiveFOVLH(float fovAngle, int width, int height, float nearZ, float farZ)
	{
		float yScale = 1.0f / Math::Tan(fovAngle * 0.5f);
		float xScale = yScale / (width / height);

		Matrix4D M;
		M = M.Zero();
		M._m.m00 = xScale;
		M._m.m11 = yScale;
		M._m.m22 = (farZ * nearZ) / (farZ - nearZ);
		M._m.m23 = 1.0f;
		M._m.m32 = (-nearZ * farZ) / (farZ - nearZ);
	
		return M;
	}

	Matrix4D Matrix4D::Translate(const Vector4D& v)
	{
		return Matrix4D(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			v.X,  v.Y,  v.Z,  v.W);
	}

	Matrix4D Matrix4D::Scale(const Vector4D & v)
	{
		return Matrix4D(
			v.X, 0.0f, 0.0f, 0.0f,
			0.0f, v.Y, 0.0f, 0.0f,
			0.0f, 0.0f, v.Z, 0.0f,
			0.0f, 0.0f, 0.0f, v.W);
	}

	Matrix4D Matrix4D::Rotate(const Vector4D & v)
	{
		//rotate X:
		//1		0		0		0
		//0		cos		-sen	0
		//0		sen		cos		0
		//0		0		0		1
		//rotate Y:
		//cos	0		sen		0
		//0		1		0		0
		//-sen	0		cos		0
		//0		0		0		1
		//rotate Z:
		//cos	-sen	0		0
		//sen	cos		0		0
		//0		0		1		0
		//0		0		0		1

		//Matrix4D RotateX;
		//Matrix4D RotateY;
		//Matrix4D RotateZ;

		Matrix4D FinalRotation;
		FinalRotation = RotateX(v.X) * RotateY(v.Y) * RotateZ(v.Z);
		//RotateX = Zero();
		//RotateY = Zero();
		//RotateZ = Zero();
		/////vemos que tenga rotación en X
		//if (v.X != 0)
		//{
		//	RotateX.m[0][0] = 1;
		//	RotateX.m[1][1] = Math::Cos(v.X);
		//	RotateX.m[1][2] = -Math::Sin(v.X);
		//	RotateX.m[2][1] = Math::Sin(v.X);
		//	RotateX.m[2][2] = Math::Cos(v.X);
		//	RotateX.m[3][3] = 1;
		//}
		/////rotación en Y
		//if (v.Y != 0)
		//{
		//	RotateY.m[0][0] = Math::Cos(v.Y);
		//	RotateY.m[0][2] = Math::Sin(v.Y);
		//	RotateY.m[1][1] = 1;
		//	RotateY.m[0][2] = -Math::Sin(v.Y);
		//	RotateY.m[2][2] = Math::Cos(v.Y);
		//	RotateY.m[3][3] = 1;
		//}
		/////Rotación en Z
		//if (v.Z != 0)
		//{
		//	RotateZ.m[0][0] = Math::Cos(v.Z);
		//	RotateZ.m[0][1] = -Math::Sin(v.Z);
		//	RotateZ.m[1][0] = Math::Sin(v.Z);
		//	RotateZ.m[1][1] = Math::Cos(v.Z);
		//	RotateZ.m[2][2] = 1;
		//	RotateZ.m[3][3] = 1;
		//}
		//FinalRotation = RotateX * RotateY * RotateZ;
		//FinalRotation.Transpose();
		return FinalRotation;
	}

	Matrix4D Matrix4D::RotateX(float angle)
	{
		Matrix4D RotateX;
		RotateX.Zero();
		RotateX.m[0][0] = 1;
		RotateX.m[1][1] = Math::Cos(angle);
		RotateX.m[1][2] = -Math::Sin(angle);
		RotateX.m[2][1] = Math::Sin(angle);
		RotateX.m[2][2] = Math::Cos(angle);
		RotateX.m[3][3] = 1;

		RotateX.Transpose();
		return RotateX;
	}

	Matrix4D Matrix4D::RotateY(float angle)
	{
		Matrix4D RotateY;
		RotateY.Zero();
		RotateY.m[0][0] = Math::Cos(angle);
		RotateY.m[0][2] = Math::Sin(angle);
		RotateY.m[1][1] = 1;
		RotateY.m[0][2] = -Math::Sin(angle);
		RotateY.m[2][2] = Math::Cos(angle);
		RotateY.m[3][3] = 1;

		RotateY.Transpose();
		return RotateY;
	}

	Matrix4D Matrix4D::RotateZ(float angle)
	{
		Matrix4D RotateZ;
		RotateZ.Zero();

		RotateZ.m[0][0] = Math::Cos(angle);
		RotateZ.m[0][1] = -Math::Sin(angle);
		RotateZ.m[1][0] = Math::Sin(angle);
		RotateZ.m[1][1] = Math::Cos(angle);
		RotateZ.m[2][2] = 1;
		RotateZ.m[3][3] = 1;

		RotateZ.Transpose();
		return RotateZ;
	}

	Matrix4D& Matrix4D::Transpose()
	{
		Matrix4D R;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				R.m[i][j] = m[j][i];
			}
		}

		*this = R;
		return *this;
	}

	Matrix4D Matrix4D::Transpose(Matrix4D M)
	{
		Matrix4D R = Zero();

		//R._m.m00 = M._m.m00;	R._m.m01 = M._m.m10;	R._m.m02 = M._m.m20	R._m.m30 = M._m.m30;
		//R._m.m10 = M._m.m01;	R._m.m11 = M._m.m11;	R._m.m12 = M._m.m21;	R._m.m31 = M._m.m31;
		//R._m.m20 = M._m.m02;	R._m.m21 = M._m.m12;	R._m.m22 = M._m.m22;	R._m.m32 = M._m.m32;
		//R._m.m30 = M._m.m03;	R._m.m31 = M._m.m13;	R._m.m32 = M._m.m22;	R._m.m33 = M._m.m33;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				R.m[i][j] = M.m[j][i];
			}
		}

		return R;
	}

	Matrix4D Matrix4D::operator*(Matrix4D M)
	{
		///enteros que se usan para los for.
		int i, j, k;
		///inicializamos en 0 la matriz.
		Matrix4D R = Zero();

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 4; k++)
				{
					R.m[i][j] += m[j][k] * M.m[k][i];
				}
			}
		}

		return R;
	}

	Vector4D Matrix4D::operator*(Vector4D V)
	{
		//Matrix4D R = Zero();
		Vector4D R;
		R.X = (_m.m00 * V.X) + (_m.m01 * V.Y) + (_m.m02 * V.Z) + (_m.m03 * V.W);
		R.Y = (_m.m10 * V.X) + (_m.m11 * V.Y) + (_m.m12 * V.Z) + (_m.m13 * V.W);
		R.Z = (_m.m20 * V.X) + (_m.m21 * V.Y) + (_m.m22 * V.Z) + (_m.m23 * V.W);
		R.W = (_m.m30 * V.X) + (_m.m31 * V.Y) + (_m.m32 * V.Z) + (_m.m33 * V.W);
		//R._m.m00 = _m.m00 * V.X + _m.m00 * V.Y + _m.m00 * V.Z + _m.m00 * V.W;
		//R._m.m01 = _m.m01 * V.X + _m.m01 * V.Y + _m.m01 * V.Z + _m.m01 * V.W;
		//R._m.m02 = _m.m02 * V.X + _m.m02 * V.Y + _m.m02 * V.Z + _m.m02 * V.W;
		//R._m.m03 = _m.m03 * V.X + _m.m03 * V.Y + _m.m03 * V.Z + _m.m03 * V.W;

		//R._m.m10 = _m.m10 * V.X + _m.m10 * V.Y + _m.m10 * V.Z + _m.m10 * V.W;
		//R._m.m11 = _m.m11 * V.X + _m.m11 * V.Y + _m.m11 * V.Z + _m.m11 * V.W;
		//R._m.m12 = _m.m12 * V.X + _m.m12 * V.Y + _m.m12 * V.Z + _m.m12 * V.W;
		//R._m.m13 = _m.m13 * V.X + _m.m13 * V.Y + _m.m13 * V.Z + _m.m13 * V.W;

		//R._m.m20 = _m.m20 * V.X + _m.m20 * V.Y + _m.m20 * V.Z + _m.m20 * V.W;
		//R._m.m21 = _m.m21 * V.X + _m.m21 * V.Y + _m.m21 * V.Z + _m.m21 * V.W;
		//R._m.m22 = _m.m22 * V.X + _m.m22 * V.Y + _m.m22 * V.Z + _m.m22 * V.W;
		//R._m.m23 = _m.m23 * V.X + _m.m23 * V.Y + _m.m23 * V.Z + _m.m23 * V.W;

		return R;
	}

	Matrix4D Matrix4D::operator+(Matrix4D M)
	{
		Matrix4D R = Zero();
		R._m.m00 = _m.m00 + M._m.m00;	R._m.m01 = _m.m01 + M._m.m01;	R._m.m02 = _m.m02 + M._m.m02;	R._m.m03 = _m.m03 + M._m.m03;
		R._m.m10 = _m.m10 + M._m.m10;	R._m.m11 = _m.m11 + M._m.m11;	R._m.m12 = _m.m12 + M._m.m12;	R._m.m13 = _m.m13 + M._m.m13;
		R._m.m20 = _m.m20 + M._m.m20;	R._m.m21 = _m.m21 + M._m.m21;	R._m.m22 = _m.m22 + M._m.m22;	R._m.m23 = _m.m23 + M._m.m23;
		R._m.m30 = _m.m30 + M._m.m30;	R._m.m31 = _m.m31 + M._m.m31;	R._m.m32 = _m.m32 + M._m.m32;	R._m.m33 = _m.m33 + M._m.m33;

		return R;
	}

	Matrix4D Matrix4D::operator+(Vector4D V)
	{
		Matrix4D R = Zero();
		R._m.m00 = _m.m00 + V.X;	R._m.m01 = _m.m01 + V.Y;	R._m.m02 = _m.m02 + V.Z + R._m.m03 + V.W;
		R._m.m10 = _m.m10 + V.X;	R._m.m11 = _m.m11 + V.Y;	R._m.m12 = _m.m12 + V.Z + R._m.m13 + V.W;
		R._m.m20 = _m.m20 + V.X;	R._m.m21 = _m.m21 + V.Y;	R._m.m22 = _m.m22 + V.Z + R._m.m23 + V.W;
		R._m.m30 = _m.m30 + V.X;	R._m.m31 = _m.m31 + V.Y;	R._m.m32 = _m.m32 + V.Z + R._m.m33 + V.W;

		return R;
	}

	Matrix4D Matrix4D::operator-(Matrix4D M)
	{
		Matrix4D R = Zero();
		R._m.m00 = _m.m00 - M._m.m00;	R._m.m01 = _m.m01 - M._m.m01;	R._m.m02 = _m.m02 - M._m.m02;	R._m.m03 = _m.m03 - M._m.m03;
		R._m.m10 = _m.m10 - M._m.m10;	R._m.m11 = _m.m11 - M._m.m11;	R._m.m12 = _m.m12 - M._m.m12;	R._m.m13 = _m.m13 - M._m.m13;
		R._m.m20 = _m.m20 - M._m.m20;	R._m.m21 = _m.m21 - M._m.m21;	R._m.m22 = _m.m22 - M._m.m22;	R._m.m23 = _m.m23 - M._m.m23;
		R._m.m30 = _m.m30 - M._m.m30;	R._m.m31 = _m.m31 - M._m.m31;	R._m.m32 = _m.m32 - M._m.m32;	R._m.m33 = _m.m33 - M._m.m33;

		return R;
	}
	Matrix4D Matrix4D::operator-(Vector4D V)
	{
		Matrix4D R = Zero();
		R._m.m00 = _m.m00 - V.X;	R._m.m01 = _m.m01 - V.Y;	R._m.m02 = _m.m02 - V.Z + R._m.m03 - V.W;
		R._m.m10 = _m.m10 - V.X;	R._m.m11 = _m.m11 - V.Y;	R._m.m12 = _m.m12 - V.Z + R._m.m13 - V.W;
		R._m.m20 = _m.m20 - V.X;	R._m.m21 = _m.m21 - V.Y;	R._m.m22 = _m.m22 - V.Z + R._m.m23 - V.W;
		R._m.m30 = _m.m30 - V.X;	R._m.m31 = _m.m31 - V.Y;	R._m.m32 = _m.m32 - V.Z + R._m.m33 - V.W;

		return R;
	}
}