#pragma once
#include "BEPrerequisitesEngine.h"
#include <assimp/material.h>

namespace BlackEngine
{
	class BEResource;
	class BEShaderResourceView;
	struct GraphicsAPIData;

	class BE_ENGINE_EXPORT BEMaterial
	{
	public:
		BEMaterial();
		~BEMaterial();

		void Initialize();
		void Destroy();

		BEShaderResourceView* m_Textures[aiTextureType_UNKNOWN];

		///coeficiente de brillo.
		float m_Shininess;
		float m_ShininessStrenght;
	};
}