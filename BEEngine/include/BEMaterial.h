#pragma once
#include "BEPrerequisitesEngine.h"

namespace BlackEngine
{
	class BEResource;

	class BE_ENGINE_EXPORT BEMaterial
	{
	public:
		BEMaterial();
		~BEMaterial();

		void Initialize();
		void Destroy();

		BEResource* m_Diffuse;
	};
}