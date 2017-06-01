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

	bool BEShaderResourceView::Create(const GraphicsAPIData * GData, BETexture resource)
	{
		HRESULT hRes;
		hRes = GData->m_Device->CreateShaderResourceView(
			resource.m_TextureData->m_Texture2D ,NULL, &m_SRVData->m_SRV);

		if (FAILED(hRes))
		{
			return false;
		}

		return true;
	}
}