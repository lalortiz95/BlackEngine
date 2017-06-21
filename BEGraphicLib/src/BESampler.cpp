#include "BESampler.h"
#include "DirectXData.h"

namespace BlackEngine
{
	BESampler::BESampler()
	{
		m_SD = nullptr;
		Initialize();
	}

	BESampler::~BESampler()
	{
	}

	void BESampler::Initialize()
	{
		Destroy();
		m_SD = new SamplerData();
	}

	void BESampler::Destroy()
	{
		if (m_SD != nullptr)
		{
			m_SD->Destroy();
			delete m_SD;
			m_SD = nullptr;
		}
	}

	void BESampler::Create(const GraphicsAPIData * GData)
	{
		/// Create the sample state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		HRESULT hr = GData->m_Device->CreateSamplerState(&sampDesc, &m_SD->m_samplerState);

		if (FAILED(hr))
		{
			return;
		}
	}
}