#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BEGraphicsAPI.h"
#include "BERenderTargetView.h"

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
		bool CreateTextureFromFile(const GraphicsAPIData*, const String& name);
		bool CreateAsDepthStencil(const GraphicsAPIData* GData, int width, int height/*, BETexture*&*/);
		bool CreateAsRenderTarget(const GraphicsAPIData* GData, int width, int height);
		void Destroy();

		TextureData* m_TextureData;
	private:
		///variable que almacena el nuevo RTV
		BERenderTargetView m_RTV;
		
	};
}