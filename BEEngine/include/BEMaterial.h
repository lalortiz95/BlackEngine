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

		//TODO: mover el mesh a ete proyecto.

		BEResource* m_Diffuse;
	};
}