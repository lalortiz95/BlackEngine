#include "Quaternion.h"
#include "BEMath.h"

namespace BlackEngine
{

	void Quaternion::Normalize()
	{
		///Inverza de la magnitud
		float magnitude = 1.0f / sqrt((w*w) + (x*x) + (y*y) + (z*z));

		///Se normaliza.
		w *= magnitude;
		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}

	void Quaternion::RotateLocal(Vector3D Axis, float fAngle)
	{
		/// Where we store the local rotation
		Quaternion LocalRotation;
		/// we calculate with the given angle, and axis.
		LocalRotation.w = Math::Cos(fAngle / 2);
		LocalRotation.x = Axis.X * Math::Sin(fAngle / 2);
		LocalRotation.y = Axis.Y * Math::Sin(fAngle / 2);
		LocalRotation.z = Axis.Z * Math::Sin(fAngle / 2);
	}

	Matrix4D Quaternion::ConvertToMatrix()
	{
		Matrix4D R;
		//TODO: aplicar.
		return R;
	}
	
	Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		Quaternion R;

		R.w = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
		R.x = (w * q.x) + (x * q.w) + (y * q.z) - (z * q.y);
		R.y = (w * q.y) - (x * q.z) + (y * q.w) + (z * q.x);
		R.z = (w * q.z) + (x * q.y) - (y * q.x) + (z * q.w);

		return R;
	}
}