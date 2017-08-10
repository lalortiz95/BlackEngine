#pragma once
#include "BEPrerequisitesUtility.h"
#include "Vector3D.h"
#include "Matrix4D.h"

///The engine's namespace.
namespace BlackEngine
{
	///Declaration of the quaternion class.
	class BE_UTILITY_EXPORT Quaternion
	{
	public:
		/// Stores in which axis is the quaternion rotating, and how much.
		float x, y, z, w;
		Quaternion();
		Quaternion(float fx, float fy, float fz, float fw);
		Quaternion(const Quaternion& q);
		~Quaternion();

		/// This function normalizes the quaternion.
		void Normalize();
		/// Rotates in it's local space, it's given  in which angles and how much.
		void RotateLocal(Vector3D, float);
		/// Converts a quaternion to a fourth dimensional matrix.
		Matrix4D ConvertToMatrix();
		/// Compares two quaternions with a tolerance for decimals.
		bool Equal(const Quaternion& q, float tolerance = Math::DELTA);
		/// Assign new values to the quaternion.
		void Set(float fx, float fy, float fz, float fw);

		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator+(const Quaternion& q) const;
		Quaternion operator-(const Quaternion& q) const;

		Quaternion& operator*=(const Quaternion& q);
		Quaternion& operator+=(const Quaternion& q);
		Quaternion& operator-=(const Quaternion& q);

		bool operator==(const Quaternion& q) const;
	};
}