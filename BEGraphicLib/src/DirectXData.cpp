#include "DirectXData.h"

#include "BEInputLayout.h"
#include "BEVertexBuffer.h"
#include "BEIndexBuffer.h"


namespace BlackEngine
{
	void GraphicsAPIData::Initialize()
	{
		m_ShaderData = new ShaderData();
		m_VB = new BEVertexBuffer();
		m_VB->Initialize();
		m_IB = new BEIndexBuffer();
		m_IB->Initialize();
		m_IL = new BEInputLayout();
		m_IL->Initialize();
	}

	void GraphicsAPIData::Destroy()
	{
		if (m_Device != nullptr)
		{
			m_Device->Release();
			m_Device = nullptr;
		}
		if (m_SwapChain != nullptr)
		{
			m_SwapChain->Release();
			m_SwapChain = nullptr;
		}
		if (m_DeviceContext != nullptr)
		{
			m_DeviceContext->Release();
			m_DeviceContext = nullptr;
		}
		if (m_IL != nullptr)
		{
			m_IL->Destroy();
			m_IL = nullptr;
		}
		if (m_IB != nullptr)
		{
			m_IB->Destroy();
			m_IB = nullptr;
		}
		if (m_VB != nullptr)
		{
			m_VB->Destroy();
			m_VB = nullptr;
		}
		if (m_ShaderData != nullptr)
		{
			m_ShaderData->Destroy();
			m_ShaderData = nullptr;
		}
	}

	void InputLayoutData::Destroy()
	{
		if (m_InputLayout != nullptr)
		{
			m_InputLayout->Release();
			m_InputLayout = nullptr;
		}
	}
}