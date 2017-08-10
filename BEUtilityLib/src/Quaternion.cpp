#include "Quaternion.h"
#include "BEMath.h"

namespace BlackEngine
{
	Quaternion::Quaternion()
	{

	}

	Quaternion::Quaternion(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	Quaternion::Quaternion(const Quaternion & q)
	{
		*this = q;
	}

	Quaternion::~Quaternion()
	{
	}

	void Quaternion::Normalize()
	{
		///Inversa de la magnitud
		float magnitude = 1.0f / sqrt((w*w) + (x*x) + (y*y) + (z*z));

		///Se normaliza.
		w *= magnitude;
		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}

	void Quaternion::RotateLocal(Vector3D Axis, float fAngle)
	{
		/// we calculate with the given angle, and axis.
		w = Math::Cos(fAngle / 2);
		x = Axis.X * Math::Sin(fAngle / 2);
		y = Axis.Y * Math::Sin(fAngle / 2);
		z = Axis.Z * Math::Sin(fAngle / 2);
	}

	Matrix4D Quaternion::ConvertToMatrix()
	{
		Matrix4D R = R.Identity();
		R.m[0][0] = 1 - (2 * (y*y) - (2 * (z*z)));
		R.m[0][1] = (2 * x*y) + (2 * w*z);
		R.m[0][2] = (2 * x*z) - (2 * w*y);

		R.m[1][0] = (2 * x*y) - (2 * w*z);
		R.m[1][1] = 1 - (2 * (x*x) - (2 * (z*z)));
		R.m[1][2] = (2 * y*z) - (2 * w*x);

		R.m[2][0] = (2 * x*z) + (2 * w*y);
		R.m[2][1] = (2 * y*z) + (2 * w*x);
		R.m[2][2] = 1 - (2 * (x*x) - (2 * (y*y)));

		return R;
	}

	bool Quaternion::Equal(const Quaternion & q, float tolerance)
	{
		return (std::fabsf(x - q.x) <= tolerance &&
				std::fabsf(y - q.y) <= tolerance &&
				std::fabsf(z - q.z) <= tolerance &&
				std::fabsf(w - q.w) <= tolerance);
	}

	void Quaternion::Set(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}

	Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		/// The quaternion to return.
		Quaternion R;

		R.w = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
		R.x = (w * q.x) + (x * q.w) + (y * q.z) - (z * q.y);
		R.y = (w * q.y) - (x * q.z) + (y * q.w) + (z * q.x);
		R.z = (w * q.z) + (x * q.y) - (y * q.x) + (z * q.w);

		return R;
	}

	Quaternion Quaternion::operator+(const Quaternion & q) const
	{
		return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}
	
	Quaternion Quaternion::operator-(const Quaternion & q) const
	{
		return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	Quaternion & Quaternion::operator*=(const Quaternion & q)
	{
		x *= q.x;
		y *= q.y;
		z *= q.z;
		w *= q.w;
		return *this;
	}

	Quaternion & Quaternion::operator+=(const Quaternion & q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}

	Quaternion & Quaternion::operator-=(const Quaternion & q)
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
		return *this;
	}

	bool Quaternion::operator==(const Quaternion & q) const
	{
		return (x == q.x && y == q.y && z == q.z && w == q.w);
	}
}