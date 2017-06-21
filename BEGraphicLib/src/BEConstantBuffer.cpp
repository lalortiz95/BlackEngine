#include "BEConstantBuffer.h"
#include "DirectXData.h"
#include <Matrix4D.h>

namespace BlackEngine
{
	BEConstantBuffer::BEConstantBuffer()
	{
		m_BufferData = nullptr;
		Initialize();
	}

	BEConstantBuffer::~BEConstantBuffer()
	{
		Destroy();
	}

	void BEConstantBuffer::Destroy()
	{
		if (m_BufferData != nullptr)
		{
			delete m_BufferData;
			m_BufferData = nullptr;
		}
	}

	bool BEConstantBuffer::CreateBuffer(const GraphicsAPIData * pGraphicData)
	{
		Destroy();
		m_BufferData = new BufferData();
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(Matrix4D);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = pGraphicData->m_Device->CreateBuffer(&bufferDesc, NULL, &m_BufferData->m_Buffer);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}
}