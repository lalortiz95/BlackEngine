#include "GraphicsUnitTest.h"
#include <DirectXData.h>
#include <BEVertexBuffer.h>
#include <BEIndexBuffer.h>
#include <BEConstantBuffer.h>
#include <BESampler.h>
#include <BEModel.h>
#include <BEVertexShader.h>
#include <BEPixelShader.h>
#include <BEInputLayout.h>
#include <BETexture.h>
#include <BEShaderResourceView.h>
#include <BERasterizerState.h>
#include <BEResource.h>
#include <BETextureResource.h>
#include <BEModelResource.h>
#include <BEParser.h>

#include <BEResourceManager.h>
//#include <xnamath.h>

namespace BlackEngine
{
	struct CBNeverChanges
	{
		Matrix4D m_View;
	};

	struct CBChangeOnResize
	{
		Matrix4D m_Projection;
	};

	struct CBChangesEveryFrame
	{
		Matrix4D m_World;
		Vector4D m_MeshColor;
	};

	GraphicsUnitTest::GraphicsUnitTest()
	{

	}

	GraphicsUnitTest::~GraphicsUnitTest()
	{
	}

	void GraphicsUnitTest::OnInitialize()
	{
		//Esto deber�a ser un modulo.

		m_ColorSampler = new BESampler();
		m_ColorSampler->Initialize();
		m_Model = new BEModel();

		///constant buffers.
		m_BNeverChanges = new BEConstantBuffer();
		m_BNeverChanges->Initialize();
		m_BChangeOnResize = new BEConstantBuffer();
		m_BChangeOnResize->Initialize();
		m_BChangesEveryFrame = new BEConstantBuffer();
		m_BChangesEveryFrame->Initialize();
		m_ColorMap = new BEShaderResourceView();
		m_ColorMap->Initialize();
		m_RasterizerState = new BERasterizerState();
		m_RasterizerState->Initialize();
		m_ResourceManager = new BEResourceManager();
		m_ResourceManager->Initialize();

		m_MeshColor.X = 0.7f;
		m_MeshColor.Y = 0.7f;
		m_MeshColor.Z = 0.7f;
		m_MeshColor.W = 1.0f;

		if (!CreatePixelAndVertexShader())
		{
			//Ayudaaaa
		}
		///creamos y seteamos el vertex buffer.
		m_GraphicsAPI->m_pGraphicsAPIData->m_IL->CreateInputLayout(*m_GraphicsAPI->m_pGraphicsAPIData, m_VS);

		///guardo la graphic api en la variable miembra del resource manager.
		m_ResourceManager->m_GA = m_GraphicsAPI;
		///cargo los recursos y los introduzco en el vector.
		m_ResourceVector.push_back(m_ResourceManager->LoadResourceFromFile("Resources\\Models\\samus.fbx"));
		/*m_ResourceVector.push_back(m_ResourceManager->LoadResourceFromFile
		("C:\\Users\\Lalo\\Documents\\School\\6to cuatrimestre\\Motores\\BlackEngine\\bin\\Resources\\Textures\\samus\\mat2_a.jpg"));
		m_ResourceVector.push_back(m_ResourceManager->LoadResourceFromFile
		("C:\\Users\\Lalo\\Documents\\School\\6to cuatrimestre\\Motores\\BlackEngine\\bin\\Resources\\Textures\\samus\\mat2_ao.jpg"));*/

		/// select which primtive type we are using
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->IASetPrimitiveTopology
		(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);

		if (!m_BNeverChanges->CreateBuffer(m_GraphicsAPI->m_pGraphicsAPIData))
		{
			//c�mara no funciono.
		}
		m_BChangeOnResize->CreateBuffer(m_GraphicsAPI->m_pGraphicsAPIData);
		m_BChangesEveryFrame->CreateBuffer(m_GraphicsAPI->m_pGraphicsAPIData);

		String Addr("C:\\Users\\Lalo\\Documents\\School\\6to cuatrimestre\\Motores\\BlackEngine\\bin\\Resources\\Textures\\samus\\mat2_a.jpg");

		///creo el shader resource view.
		m_ColorMap->Create(m_GraphicsAPI->m_pGraphicsAPIData, &Addr);

		/// Create the sample state
		m_ColorSampler->Create(m_GraphicsAPI->m_pGraphicsAPIData);

		///creamos el rasterizer state.
		m_RasterizerState->Create(m_GraphicsAPI->m_pGraphicsAPIData);

		m_World = m_World.Identity();

		Matrix4D M;
		///inicializamos la matriz de vista.
		Vector4D Eye(5.0f, 5.0f, -5.0f, 0.0f);
		Vector4D At(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4D Up(0.0f, 1.0f, 0.0f, 0.0f);
		m_View = M.LookAtLH(Eye, At, Up);

		///matriz de proyecci�n.
		m_Projection = m_Projection.PerspectiveFOVLH
		(Math::QUARTER_PI, m_Width, m_Height, 0.01f, 100.0f);
	}

	void GraphicsUnitTest::Update(float /*delta*/)
	{

	}

	void GraphicsUnitTest::Render()
	{
		//esto es si queremos que tome la funci�n render del padre.
		//__super::Render();

		///limpiamos el back buffer.
		Vector4D CleanUpColor = { 0.0f, 0.125f, 0.3f, 1.0f };
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->ClearRenderTargetView(
			m_GraphicsAPI->GetRTV()->m_RenderTargetView, &CleanUpColor.X);

		///limpiamos el depth buffer.
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->ClearDepthStencilView(
			m_GraphicsAPI->GetDSV()->m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		CBNeverChanges cbNeverChanges;
		cbNeverChanges.m_View = m_View;
		cbNeverChanges.m_View.Transpose();
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BNeverChanges->m_BufferData->m_Buffer, 0, NULL, &cbNeverChanges, 0, 0);

		CBChangeOnResize cbChangesOnResize;
		cbChangesOnResize.m_Projection = m_Projection;
		cbChangesOnResize.m_Projection.Transpose();
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BChangeOnResize->m_BufferData->m_Buffer, 0, NULL, &cbChangesOnResize, 0, 0);

		///variables que cambian cada frame
		CBChangesEveryFrame cb;
		cb.m_World = m_World;
		cb.m_MeshColor = m_MeshColor;
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BChangesEveryFrame->m_BufferData->m_Buffer, 0, NULL, &cb, 0, 0);

		///pinto el modelo
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetShader
		(m_VS->m_VSData->m_VertexShader, NULL, 0);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(0, 1, &m_BNeverChanges->m_BufferData->m_Buffer);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(1, 1, &m_BChangeOnResize->m_BufferData->m_Buffer);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(2, 1, &m_BChangesEveryFrame->m_BufferData->m_Buffer);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->PSSetShader
		(m_PS->m_PSData->m_PixelShader, NULL, 0);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->PSSetShaderResources
		(0, 1, &m_ColorMap->m_SRVData->m_SRV);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->PSSetSamplers
		(0, 1, &m_ColorSampler->m_SD->m_samplerState);

		for(auto& res : m_ResourceVector)
		{
			if (res->GetResourceType() == RT_MODEL)
			{
				dynamic_cast<BEModelResource*>(res)->m_Model->Render(m_GraphicsAPI->m_pGraphicsAPIData);
			}
		}

		///switch the back buffer and the front buffer
		m_GraphicsAPI->m_pGraphicsAPIData->m_SwapChain->Present(0, 0);
	}

	bool GraphicsUnitTest::CreatePixelAndVertexShader()
	{
		m_VS = new BEVertexShader();
		m_VS->Initialize();
		m_PS = new BEPixelShader();
		m_PS->Initialize();

		if (!m_VS->CreateShader(m_GraphicsAPI->m_pGraphicsAPIData, "Resources\\Shaders\\VertexShader.hlsl", "vs_5_0", "VSMain"))
		{
			std::cout << "no se pudo crear VS" << std::endl;
		}
		if (!m_PS->CreateShader(m_GraphicsAPI->m_pGraphicsAPIData, "Resources\\Shaders\\PixelShader.hlsl", "ps_5_0", "PSMain"))
		{
			std::cout << "no se puedo crear PS" << std::endl;
		}

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetShader(m_VS->m_VSData->m_VertexShader, 0, 0);
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->PSSetShader(m_PS->m_PSData->m_PixelShader, 0, 0);

		return true;
	}
}
