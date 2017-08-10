#include "Matrix3D.h"

namespace BlackEngine
{
	Matrix3D::Matrix3D(
		float X0, float Y0, float Z0, 
		float X1, float Y1, float Z1,
		float X2, float Y2, float Z2)
	{
		_m.m00 = X0; _m.m01 = Y0; _m.m02 = Z0;
		_m.m10 = X1; _m.m11 = Y1; _m.m12 = Z1;
		_m.m20 = X2; _m.m21 = Y2; _m.m22 = Z2;
	}

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

	Matrix3D Matrix3D::Identity()
	{
		Matrix3D Identity = Zero();
		Identity._m.m00 = 1;
		Identity._m.m11 = 1;
		Identity._m.m22 = 1;
		return Identity;
	}

	void Matrix3D::Inverse()
	{
		float determinante = 0;
		Matrix3D TransposedMatrix;
		Matrix3D AdjunctedMatrix;

		/// Calculamos la determinante.
		determinante =
			(m[0][0] * m[1][1] * m[2][2]) + (m[0][2] * m[1][0] * m[2][1]) +
			(m[2][0] * m[0][1] * m[1][2]) - (m[2][0] * m[1][1] * m[0][2]) -
			(m[0][0] * m[1][2] * m[2][1]) - (m[2][2] * m[0][1] * m[1][0]);

		/// Revisamos que se pueda sacar su inversa.
		if (determinante != 0)
		{
			///Es posible
			/// Calculamos la transpuesta.
			TransposedMatrix = Transpose(*this);
			///Calculamos la adjunta de la matriz una vez que ya fue transpuessta.
			AdjunctedMatrix = GetAdjunct(TransposedMatrix);

			*this = AdjunctedMatrix / determinante;
		}
	}

	Matrix3D Matrix3D::GetAdjunct(Matrix3D M)
	{
		Matrix3D Adjunct;
		/// Inicializamos en 0 la matriz adjunta.
		Adjunct = Zero();

		///Calculamos cada lugar de la adjunta.
		for (int32 i = 0; i < 3; ++i)
			for (int32 j = 0; j < 3; ++j)
				Adjunct.m[i][j] = GetDeterminant(M, i, j);

		///La regresamos.
		return Adjunct;
	}

	float Matrix3D::GetDeterminant(Matrix3D M, int32 col, int32 row)
	{
		///Los valores que hay en la matriz cuando se ignoran la col y la row dada.
		float fValues[4];
		///contador para llenar fValues
		int iCount = 0;
		///
		float fDeterminant = 0;

		///guardamos los valores que no están en la columna ni en la fila dada.	
		for (int32 i = 0; i < 3; ++i)
			for (int32 j = 0; j < 3; ++j)
			{
				if (i != col && j != row)
				{
					fValues[iCount] = M.m[i][j];
					iCount++;
				}
			}

		///Calculamos la adjunta del lugar dado.
		float fElevated = Math::Power(-1, ((col + 1) + (row + 1)));
		return fElevated * (fValues[0] * fValues[3] - fValues[1] * fValues[2]);
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

	Matrix3D Matrix3D::operator/(float fVal)
	{
		Matrix3D R = Zero();
		if (fVal != 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					R.m[i][j] = m[i][j] / fVal;
				}
			}
		}

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

		return (count == 9);
		//if (count == 9)
		//{
		//	return true;
		//}
		//else
		//{
		//	return false;
		//}
	}
}