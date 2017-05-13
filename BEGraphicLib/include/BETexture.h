#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BEGraphicsAPI.h"

namespace BlackEngine
{
	struct TextureData;

	class BE_GRAPHICS_EXPORT BETexture
	{
	public:
		BETexture();
		~BETexture();

		void Initialize();
		bool CreateTexture(const GraphicsAPIData* GData, int width, int height);
		bool CreateTextureFromFile(const String& name, const GraphicsAPIData*);
		bool CreateAsDepthStencil(const GraphicsAPIData* GData, int width, int height, BETexture*&);
		void Destroy();

		TextureData* m_TextureData;
	private:
		
		//BETexture* m_DSV;
		///TextureFromFile
	};
}