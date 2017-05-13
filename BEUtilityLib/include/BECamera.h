#pragma once
#include "BEPrerequisitesUtility.h"

namespace BlackEngine
{
	class Vector3D;

	class BE_UTILITY_EXPORT BECamera
	{
	public:
		BECamera();
		~BECamera();
	
		Vector3D* m_position;
		float m_fDirection;
		float m_fUp;
	};
}