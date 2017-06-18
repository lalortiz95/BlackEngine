#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BEGraphicsAPI.h"
#include "BERenderTargetView.h"

namespace BlackEngine
{
	struct TextureData;

	namespace TEXTURE_CREATION 
	{
		enum E 
		{
			kDefault = 0x00,
			kRenderTarget = 0x01,
			kDepthStencil = 0x02,
			kShaderResource = 0x03
		};
	}

	class BE_GRAPHICS_EXPORT BETexture
	{
	public:
		BETexture();
		~BETexture();

		void Initialize();
		bool CreateTexture(const GraphicsAPIData* GData, int width, int height, uint32 flags = TEXTURE_CREATION::kDefault);
		bool CreateTextureFromFile(const GraphicsAPIData*, const String& name);
		//bool CreateAsDepthStencil(const GraphicsAPIData* GData, int width, int height);
		bool CreateAsRenderTarget(const GraphicsAPIData* GData, int width, int height);
		void Destroy();

		TextureData* m_TextureData;
	private:
		///variable que almacena el nuevo RTV
		BERenderTargetView m_RTV;
		
	};
}