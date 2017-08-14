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
		/////Creamos el input layout, es un puntero para manejarlo como un arreglo 
		/////y darle más de un valor.
		//D3D11_INPUT_ELEMENT_DESC IED[] =
		//{
		//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//	{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//};
		//int numElements = ARRAYSIZE(IED);
		//HRESULT hres = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreateInputLayout
		//(
		//	IED, numElements, 
		//	VS->m_ShaderData->m_Blob->GetBufferPointer(),
		//	VS->m_ShaderData->m_Blob->GetBufferSize(),
		//	&g_GraphicsAPI().m_pGraphicsAPIData->m_IL->m_ILData->m_InputLayout
		//);
		//if (FAILED(hres))
		//{
		//	return false;
		//}
		//g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->IASetInputLayout(g_GraphicsAPI().m_pGraphicsAPIData->m_IL->m_ILData->m_InputLayout);
		//return true;
		ID3D11ShaderReflection* pVShaderReflection = nullptr;

		HRESULT hRes = D3DReflect(
			VS->m_ShaderData->m_Blob->GetBufferPointer(),
			VS->m_ShaderData->m_Blob->GetBufferSize(), 
			IID_ID3D11ShaderReflection, 
			(void**)&pVShaderReflection);

		if (FAILED(hRes))
		{
			return false;
		}
	
		D3D11_SHADER_DESC ShaderDec;
		pVShaderReflection->GetDesc(&ShaderDec);

		Vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
		
		for (uint32 i = 0; i < ShaderDec.InputParameters; ++i)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			pVShaderReflection->GetInputParameterDesc(i, &paramDesc);

			// fill out input element desc
			D3D11_INPUT_ELEMENT_DESC elementDesc;
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;

			// determine DXGI format
			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			//save element desc
			inputLayoutDesc.push_back(elementDesc);
		}

		// Try to create Input Layout
		hRes = g_GraphicsAPI().m_pGraphicsAPIData->m_Device->CreateInputLayout(
			&inputLayoutDesc[0], inputLayoutDesc.size(),
			VS->m_ShaderData->m_Blob->GetBufferPointer(),
			VS->m_ShaderData->m_Blob->GetBufferSize(),
			&m_ILData->m_InputLayout);

		//Free allocation shader reflection memory
		pVShaderReflection->Release();
		return hRes;
	}
}