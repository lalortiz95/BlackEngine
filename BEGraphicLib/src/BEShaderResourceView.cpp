#include "BEShaderResourceView.h"
#include "DirectXData.h"

#include <D3DX11tex.h>

namespace BlackEngine
{
	BEShaderResourceView::BEShaderResourceView()
	{
		m_SRVData = nullptr;
	}

	BEShaderResourceView::~BEShaderResourceView()
	{

	}

	bool BEShaderResourceView::Initialize()
	{
		if (m_SRVData != nullptr)
		{
			Destroy();
		}

		m_SRVData = new ShaderResourceViewData();

		return true;
	}

	void BEShaderResourceView::Destroy()
	{
		if (m_SRVData != nullptr)
		{
			m_SRVData->Destroy();
			delete m_SRVData;
		}
	}

	bool BEShaderResourceView::Create(const GraphicsAPIData * GData, const BETexture* resource)
	{
		HRESULT hRes;
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVD;
		SRVD.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SRVD.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVD.Texture2D.MostDetailedMip = 0;
		SRVD.Texture2D.MipLevels = 1;

		hRes = GData->m_Device->CreateShaderResourceView(
			resource->m_TextureData->m_Texture2D, &SRVD, &m_SRVData->m_SRV);

		if (FAILED(hRes))
		{
			return false;
		}

		return true;
	}
}