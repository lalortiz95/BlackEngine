#include "Matrix3D.h"

namespace BlackEngine
{
	Matrix3D::~Matrix3D()
	{

	}

	Matrix3D Matrix3D::Zero()
	{
		Matrix3D R;
		memset(&R, 0, sizeof(R));
		return R;
	}

	Matrix3D Matrix3D::Transpose(Matrix3D M)
	{
		Matrix3D R = Zero();

		//R._m.m00 = M._m.m00;	R._m.m01 = M._m.m10;	R._m.m02 = M._m.m20;
		//R._m.m10 = M._m.m01;	R._m.m11 = M._m.m11;	R._m.m12 = M._m.m21;
		//R._m.m20 = M._m.m02;	R._m.m21 = M.m12;	R._m.m22 = M._m.m22;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				R.m[i][j] = M.m[j][i];
			}
		}

		return R;
	}

	Matrix3D Matrix3D::operator*(Matrix3D M)
	{
		///enteros que se usan para los for.
		int i, j, k;
		///inicializamos en 0 la matriz.
		Matrix3D R = Zero();

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				for (k = 0; k < 3; k++)
				{
					R.m[i][j] += m[j][k] * M.m[k][i];
				}
			}
		}

		return R;
	}

	Matrix3D Matrix3D::operator*(Vector3D V)
	{
		Matrix3D R = Zero();

		R._m.m00 = _m.m00 * V.X + _m.m00 * V.Y + _m.m00 * V.Z;
		R._m.m01 = _m.m01 * V.X + _m.m01 * V.Y + _m.m01 * V.Z;
		R._m.m02 = _m.m02 * V.X + _m.m02 * V.Y + _m.m02 * V.Z;

		R._m.m10 = _m.m10 * V.X + _m.m10 * V.Y + _m.m10 * V.Z;
		R._m.m11 = _m.m11 * V.X + _m.m11 * V.Y + _m.m11 * V.Z;
		R._m.m12 = _m.m12 * V.X + _m.m12 * V.Y + _m.m12 * V.Z;

		R._m.m20 = _m.m20 * V.X + _m.m20 * V.Y + _m.m20 * V.Z;
		R._m.m21 = _m.m21 * V.X + _m.m21 * V.Y + _m.m21 * V.Z;
		R._m.m22 = _m.m22 * V.X + _m.m22 * V.Y + _m.m22 * V.Z;

		return R;
	}

	Matrix3D Matrix3D::operator+(Matrix3D M)
	{
		Matrix3D R = Zero();
		R._m.m00 = _m.m00 + M._m.m00;	R._m.m01 = _m.m01 + M._m.m01;	R._m.m02 = _m.m02 + M._m.m02;
		R._m.m10 = _m.m10 + M._m.m10;	R._m.m11 = _m.m11 + M._m.m11;	R._m.m12 = _m.m12 + M._m.m12;
		R._m.m20 = _m.m20 + M._m.m20;	R._m.m21 = _m.m21 + M._m.m21;	R._m.m22 = _m.m22 + M._m.m22;

		return R;
	}

	Matrix3D Matrix3D::operator+(Vector3D V)
	{
		Matrix3D R = Zero();
		R._m.m00 = _m.m00 + V.X;	R._m.m01 = _m.m01 + V.Y;	R._m.m02 = _m.m02 + V.Z;
		R._m.m10 = _m.m10 + V.X;	R._m.m11 = _m.m11 + V.Y;	R._m.m12 = _m.m12 + V.Z;
		R._m.m20 = _m.m20 + V.X;	R._m.m21 = _m.m21 + V.Y;	R._m.m22 = _m.m22 + V.Z;

		return R;
	}

	Matrix3D Matrix3D::operator-(Matrix3D M)
	{
		Matrix3D R = Zero();
		R._m.m00 = _m.m00 - M._m.m00;	R._m.m01 = _m.m01 - M._m.m01;	R._m.m02 = _m.m02 - M._m.m02;
		R._m.m10 = _m.m10 - M._m.m10;	R._m.m11 = _m.m11 - M._m.m11;	R._m.m12 = _m.m12 - M._m.m12;
		R._m.m20 = _m.m20 - M._m.m20;	R._m.m21 = _m.m21 - M._m.m21;	R._m.m22 = _m.m22 - M._m.m22;

		return R;
	}
	Matrix3D Matrix3D::operator-(Vector3D V)
	{
		Matrix3D R = Zero();
		R._m.m00 = _m.m00 - V.X;	R._m.m01 = _m.m01 - V.Y;	R._m.m02 = _m.m02 - V.Z;
		R._m.m10 = _m.m10 - V.X;	R._m.m11 = _m.m11 - V.Y;	R._m.m12 = _m.m12 - V.Z;
		R._m.m20 = _m.m20 - V.X;	R._m.m21 = _m.m21 - V.Y;	R._m.m22 = _m.m22 - V.Z;

		return R;
	}

	bool Matrix3D::operator==(Matrix3D M)
	{
		///contador que nos indica si coincidieron todas las casillas.
		int count = 0;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (m[i][j] == M.m[i][j])
				{
					count++;
				}
			}
		}

		if (count == 9)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}