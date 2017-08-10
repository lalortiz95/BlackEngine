#include "BEIndexBuffer.h"
#include "BEGraphicsAPI.h"
#include "DirectXData.h"

namespace BlackEngine
{
	BEIndexBuffer::BEIndexBuffer()
	{
		m_BufferData = nullptr;
	}


	BEIndexBuffer::~BEIndexBuffer()
	{
		Destroy();
	}

	void BEIndexBuffer::Initialize()
	{
		
	}

	void BEIndexBuffer::Destroy()
	{
		if (m_BufferData != nullptr)
		{
			delete m_BufferData;
			m_BufferData = nullptr;
		}
	}

	bool BEIndexBuffer::CreateBuffer()
	{
		Destroy();
		m_BufferData = new BufferData();
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(uint32) * m_Indices.size();
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA srd = { 0 };
		srd.pSysMem = &m_Indices[0];

		HRESULT hr = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreateBuffer(&bufferDesc,
			&srd, &m_BufferData->m_Buffer);

		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}

	void BEIndexBuffer::AddIndex(uint32 i)
	{
		m_Indices.push_back(i);
	}
}