#include "BERasterizerState.h"
#include "BEGraphicsAPI.h"
#include "DirectXData.h"

namespace BlackEngine
{
	BERasterizerState::BERasterizerState()
	{
		m_RSData = nullptr;
		Initialize();
	}

	BERasterizerState::~BERasterizerState()
	{
		Destroy();
	}

	bool BERasterizerState::Initialize()
	{
		Destroy();
		m_RSData = new RasterizerStateData();
		return true;
	}

	void BERasterizerState::Destroy()
	{
		if (m_RSData != nullptr)
		{
			m_RSData->Destroy();
			delete m_RSData;
			m_RSData = nullptr;
		}
	}

	bool BERasterizerState::Create()
	{
		D3D11_RASTERIZER_DESC RD;
		HRESULT hr;
		ZeroMemory(&RD, sizeof(RD));
		RD.FillMode = D3D11_FILL_SOLID;
		RD.CullMode = D3D11_CULL_BACK; //para semitransparencias poner el cullfront.
		RD.FrontCounterClockwise = true;

		hr = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreateRasterizerState(&RD, &m_RSData->m_RS);

		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}
}