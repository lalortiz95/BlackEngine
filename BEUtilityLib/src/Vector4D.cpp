#include "Vector4D.h"
#include "Matrix4D.h"

namespace BlackEngine
{
	Vector4D Vector4D::operator*(const Matrix4D & M)
	{
		Vector4D R;
		R.X = (X * M.m[0][0]) + (X * M.m[1][0]) + (X * M.m[2][0]) + (X * M.m[3][0]);
		R.Z = (Z * M.m[0][1]) + (Z * M.m[1][1]) + (Z * M.m[2][1]) + (Z * M.m[3][1]);
		R.W = (W * M.m[0][2]) + (W * M.m[1][2]) + (W * M.m[2][2]) + (W * M.m[3][2]);
		R.Y = (Y * M.m[0][3]) + (Y * M.m[1][3]) + (Y * M.m[2][3]) + (Y * M.m[3][3]);

		return R;
	}
}