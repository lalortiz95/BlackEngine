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
		float w, x, y, z;

		/// This function normalizes the quaternion.
		void Normalize();
		/// Rotates in it's local space, it's given  in which angles and how much.
		void RotateLocal(Vector3D, float);
		/// Converts a quaternion to a fourth dimensional matrix.
		Matrix4D ConvertToMatrix();

		Quaternion operator*(const Quaternion& q) const; 
	};
}