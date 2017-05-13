#pragma once
#include "Vector3D.h"

namespace BlackEngine
{
	class BE_UTILITY_EXPORT Sphere
	{
	public:
		float m_Radius;
		float m_PosX;
		float m_PosY;
		float m_PosZ;

		bool IsDotInside(float x, float y, float z);
		bool IsRayTouching();
		bool IsPlaneTouching();
		bool IsSphereTouching(float x, float y, float z);
	};
}