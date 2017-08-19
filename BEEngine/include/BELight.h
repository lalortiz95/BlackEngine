#pragma once
#include "BEPrerequisitesEngine.h"
#include <Vector3D.h>

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BELight
	{
	public:
		BELight();
		~BELight();

		Vector3D m_Position;
		Vector3D m_Direction;
	};
}