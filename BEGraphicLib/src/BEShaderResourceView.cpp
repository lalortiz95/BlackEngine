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

	bool BEShaderResourceView::Create(const GraphicsAPIData * GData, const String * Addr)
	{
		HRESULT hRes;
		D3DX11CreateShaderResourceViewFromFile(
			GData->m_Device,
			Addr->c_str(),
			NULL,
			NULL,
			&m_SRVData->m_SRV,
			&hRes);

		if (FAILED(hRes))
		{
			return false;
		}

		return true;
	}
}