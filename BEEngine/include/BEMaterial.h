#pragma once
#include "BEPrerequisitesEngine.h"
#include <BEPixelShader.h>
#include <assimp/material.h>

namespace BlackEngine
{
	class BEShaderResourceView;

	class BE_ENGINE_EXPORT BEMaterial
	{
	public:
		BEMaterial();
		~BEMaterial();

		void Initialize();
		void Destroy();
		/// Array of textures.
		BEShaderResourceView* m_Textures[aiTextureType_UNKNOWN];

		///coeficiente de brillo.
		float m_Shininess;
		float m_ShininessStrenght;

		/// The shader asociated to the material.
		BEPixelShader m_PixelShader;
	};
}