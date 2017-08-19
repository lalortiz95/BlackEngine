#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BEGraphicsAPI.h"
#include "BERenderTargetView.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct TextureData;

	///Namespace for the Texture creation flags.
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

	///Declaration of the texture class.
	class BE_GRAPHICS_EXPORT BETexture
	{
	public:
		///Default constructor and destructor.
		BETexture();
		~BETexture();

		///This functions give and release memory from the class' variables.
		void Initialize();
		void Initialize(BERenderTargetView RTV);
		void Destroy();

		///Creates a texture with a given width, height, and the type of texture that it will be.
		bool CreateTexture(int width, int height, uint32 flags = TEXTURE_CREATION::kDefault);
		///Creates a texture from a given file.
		bool CreateTextureFromFile(const String& name);
		///Creates a new render target texture.
		bool CreateAsRenderTarget();

		///The texture data
		TextureData* m_TextureData;

	private:
		///variable that stores the new RTV
		BERenderTargetView m_RTV;
	};
}