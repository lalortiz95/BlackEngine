#include "BEInputLayout.h"
#include "BEVertexShader.h"
#include "BEGraphicsAPI.h"
#include "DirectXData.h"

namespace BlackEngine
{
	BEInputLayout::BEInputLayout()
	{
		m_ILData = nullptr;
	}


	BEInputLayout::~BEInputLayout()
	{
	}

	void BEInputLayout::Initialize()
	{
		Destroy();

		m_ILData = new InputLayoutData();
	}

	void BEInputLayout::Destroy()
	{
		if (m_ILData != nullptr)
		{
			m_ILData->Destroy();
			m_ILData = nullptr;
		}
	}

	bool BEInputLayout::CreateInputLayout(BEVertexShader* VS)
	{
		///Creamos el input layout, es un puntero para manejarlo como un arreglo 
		///y darle más de un valor.
		//TODO: checar  el quinto parametro de la binormal y la tangente.
		D3D11_INPUT_ELEMENT_DESC IED[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		int numElements = ARRAYSIZE(IED);

		HRESULT hres = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreateInputLayout
		(
			IED, numElements, 
			VS->m_ShaderData->m_Blob->GetBufferPointer(),
			VS->m_ShaderData->m_Blob->GetBufferSize(),
			&g_GraphicsAPI().m_pGraphicsAPIData->m_IL->m_ILData->m_InputLayout
		);

		if (FAILED(hres))
		{
			return false;
		}

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->IASetInputLayout(g_GraphicsAPI().m_pGraphicsAPIData->m_IL->m_ILData->m_InputLayout);
		return true;
	}
}