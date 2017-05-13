#include "DirectXData.h"
#include "BETexture.h"

#include <Vector4D.h>
#include <FreeImage.h>

namespace BlackEngine
{
	//struct TextureData
	//{
	//	ID3D11Texture2D* m_BackBuffer;
	//};


	static void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message)
	{
		if (fif != FIF_UNKNOWN) {
			if (FreeImage_GetFormatFromFIF(fif))
				printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
		}
	}

	BETexture::BETexture()
	{
		m_TextureData = nullptr;
	}

	BETexture::~BETexture()
	{
	}

	void BETexture::Initialize()
	{
		m_TextureData = new TextureData();
		//m_DSV = new BETexture();
	}

	bool BETexture::CreateAsDepthStencil(const GraphicsAPIData* GData, int width, int height, BETexture*& DSVTexture)
	{
		Initialize();
		//m_DSV->Initialize();

		///descriptor de la textura
		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		///creamos la textura.
		HRESULT hres = GData->m_Device->CreateTexture2D(&descDepth, NULL,
			&DSVTexture->m_TextureData->m_Texture2D);

		if (FAILED(hres))
		{
			return false;
		}
		return true;
	}

	void BETexture::Destroy()
	{
		if (m_TextureData != nullptr)
		{
			m_TextureData->Destroy();
			delete m_TextureData;
			m_TextureData = nullptr;
		}
	}

	bool BETexture::CreateTexture(const GraphicsAPIData * GData, int width, int height)
	{
		Initialize();
		D3D11_TEXTURE2D_DESC TextureDesc;

		ZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		TextureDesc.ArraySize = 1;
		TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		TextureDesc.CPUAccessFlags = 0;
		TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		TextureDesc.Height = height;
		TextureDesc.MipLevels = 1;
		TextureDesc.MiscFlags = 0;
		TextureDesc.SampleDesc.Count = 4;
		TextureDesc.SampleDesc.Quality = 1;
		TextureDesc.Usage = D3D11_USAGE_DEFAULT;
		TextureDesc.Width = width;

		GData->m_Device->CreateTexture2D(&TextureDesc, NULL, &m_TextureData->m_Texture2D);
		return true;
	}

	bool BETexture::CreateTextureFromFile(const String& name, const GraphicsAPIData *GData)
	{
		Initialize();
		D3D11_TEXTURE2D_DESC TextureDesc;
		D3D11_SUBRESOURCE_DATA SubresourceData;
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(name.c_str(), 0);
		FreeImage_SetOutputMessage(FreeImageErrorHandler);
		FIBITMAP* bitmap = FreeImage_Load(fif, name.c_str());

		if (!bitmap)
		{
			throw std::exception("cámara no se cargó la textura.");
		}

		ZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		TextureDesc.ArraySize = 1;
		TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		TextureDesc.CPUAccessFlags = 0;
		TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		TextureDesc.MipLevels = 1;
		TextureDesc.MiscFlags = 0;
		TextureDesc.SampleDesc.Count = 1;
		TextureDesc.SampleDesc.Quality = 0;
		TextureDesc.Usage = D3D11_USAGE_DEFAULT;
		TextureDesc.Width = FreeImage_GetWidth(bitmap);
		TextureDesc.Height = FreeImage_GetHeight(bitmap);

		ZeroMemory(&SubresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
		if (bitmap)
		{
			SubresourceData.pSysMem = bitmap->data;
			SubresourceData.SysMemPitch = FreeImage_GetPitch(bitmap);
			//SubresourceData.SysMemSlicePitch = FreeImage_GetLine(bitmap);
		}

		GData->m_Device->CreateTexture2D(&TextureDesc, &SubresourceData, &m_TextureData->m_Texture2D);
		
		FreeImage_Unload(bitmap);
		
		return true;
	}
}