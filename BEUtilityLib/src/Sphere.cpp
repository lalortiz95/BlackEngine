#include "Sphere.h"

namespace BlackEngine
{
	bool Sphere::IsDotInside(float x, float y, float z)
	{
		Vector3D vect;
		vect.CreateVector(Vector3D(x, y, z), Vector3D(m_PosX, m_PosY, m_PosZ));

		if (vect.GetMagnitude() <= m_Radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Sphere::IsRayTouching()
	{
		//TODO: implementar esto.
		return false;
	}

	bool Sphere::IsPlaneTouching()
	{
		//TODO: implementar esto
		return false;
	}

	bool Sphere::IsSphereTouching(float x, float y, float z)
	{
		Vector3D vect;
		vect.CreateVector(Vector3D(x, y, z), Vector3D(m_PosX, m_PosY, m_PosZ));
		if (vect.GetMagnitude() <= m_Radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}