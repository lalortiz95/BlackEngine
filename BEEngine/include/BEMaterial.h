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

		//TODO: mover el mesh a este proyecto.

		BEResource* m_Diffuse;
	};
}