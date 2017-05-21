#pragma once
#include "BEPrerequisitesEngine.h"

namespace BlackEngine
{
	class BEResource;
	struct GraphicsAPIData;

	class BE_ENGINE_EXPORT BEMaterial
	{
	public:
		BEMaterial();
		~BEMaterial();

		void Initialize();
		void Destroy();

		BEResource* m_Diffuse;
		BEResource* m_Ambiental;
		BEResource* m_Specular;
		BEResource* m_Emisive;
		BEResource* m_Normal;

		///coeficiente de brillo.
		float m_Shininess;
		float m_ShininessStrenght;
	};
}