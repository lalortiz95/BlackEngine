#include "BEBuffer.h"
#include "DirectXData.h"

///The engine's namespace.
namespace BlackEngine
{

	BEBuffer::BEBuffer()
	{
		m_BufferData = nullptr;
		Initialize();
	}


	BEBuffer::~BEBuffer()
	{
		Destroy();
	}

	void BEBuffer::Initialize()
	{
		m_BufferData = new BufferData();
	}

	void BEBuffer::Destroy()
	{
		if (m_BufferData != nullptr)
		{
			m_BufferData->Destroy();
			m_BufferData = nullptr;
		}
	}

	//bool BEBuffer::CreateBuffer(const GraphicsAPIData * pGraphicData, uint32 flags)
	//{
	//	///The buffer description.
	//	D3D11_BUFFER_DESC bufferDesc = { 0 };
	//	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//	if (flags & TEXTURE_CREATION::kRenderTarget)
	//	{
	//		///INDEX BUFFER
	//		bufferDesc.ByteWidth = sizeof(uint32) * m_Indices.size();
	//		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	}
	//	///CONSTANT BUFFER.
	//	bufferDesc.ByteWidth = sizeof(Matrix4D);
	//	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	//	HRESULT hr = pGraphicData->m_Device->CreateBuffer(&bufferDesc, NULL, &m_BufferData->m_Buffer);
	//	if (FAILED(hr))
	//	{
	//		return false;
	//	}

	//	return true;
	//}

}