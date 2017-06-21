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
		//Inicializacion de modulos sistema
		g_ResourceManager().StartUp();
		g_ResourceManager().Initialize();
		g_ResourceManager().m_GA = m_GraphicsAPI;

		m_ColorSampler = new BESampler();
		m_ColorSampler->Initialize();

		///constant buffers.
		m_BNeverChanges = new BEConstantBuffer();
		m_BNeverChanges->Initialize();
		m_BChangeOnResize = new BEConstantBuffer();
		m_BChangeOnResize->Initialize();
		m_BChangesEveryFrame = new BEConstantBuffer();
		m_BChangesEveryFrame->Initialize();
		m_RasterizerState = new BERasterizerState();
		m_RasterizerState->Initialize();

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

		///cargo los recursos y los introduzco en el vector.
		m_ResourceVector.push_back(g_ResourceManager().LoadResourceFromFile("Resources\\Models\\samus.fbx"));

		/// select which primtive type we are using
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->IASetPrimitiveTopology
		(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);

		if (!m_BNeverChanges->CreateBuffer(m_GraphicsAPI->m_pGraphicsAPIData))
		{
			//cámara no funciono.
		}
		m_BChangeOnResize->CreateBuffer(m_GraphicsAPI->m_pGraphicsAPIData);
		m_BChangesEveryFrame->CreateBuffer(m_GraphicsAPI->m_pGraphicsAPIData);

		/// Create the sample state
		m_ColorSampler->Create(m_GraphicsAPI->m_pGraphicsAPIData);

		///creamos el rasterizer state.
		m_RasterizerState->Create(m_GraphicsAPI->m_pGraphicsAPIData);

		m_World = m_World.Identity();

		Matrix4D M;
		///inicializamos la matriz de vista.
		Vector4D Eye(5.0f, 5.0f, -15.0f, 0.0f);
		Vector4D At(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4D Up(0.0f, 1.0f, 0.0f, 0.0f);
		m_View = M.LookAtLH(Eye, At, Up);

		///matriz de proyección.
		m_Projection = m_Projection.PerspectiveFOVLH
		(Math::QUARTER_PI, m_Width, m_Height, 0.01f, 100.0f);
	}

	void GraphicsUnitTest::Update(float delta)
	{
		//TODO: mover la camera, oh yeah baby!
		//TODO: obtener que tanto se va a mover según la tecla que presionó.
		//input
		//m_View.Translate();
	}

	void GraphicsUnitTest::Render()
	{
		//esto es si queremos que tome la función render del padre.
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

		///seteo el vertex shader.
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetShader
		(m_VS->m_VSData->m_VertexShader, NULL, 0);
		///se setean los constant buffers.
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(0, 1, &m_BNeverChanges->m_BufferData->m_Buffer);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(1, 1, &m_BChangeOnResize->m_BufferData->m_Buffer);

		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(2, 1, &m_BChangesEveryFrame->m_BufferData->m_Buffer);
		///se setea el pixel shader.
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->PSSetShader
		(m_PS->m_PSData->m_PixelShader, NULL, 0);
		///se setean los samplers.
		m_GraphicsAPI->m_pGraphicsAPIData->m_DeviceContext->PSSetSamplers
		(0, 1, &m_ColorSampler->m_SD->m_samplerState);
		///mando el render de los modelos.
		for (auto& res : m_ResourceVector)
		{
			if (res->GetResourceType() == RT_MODEL)
			{
				dynamic_cast<BEModelResource*>(res)->m_Model->Render(m_GraphicsAPI->m_pGraphicsAPIData);
			}
		}

		///switch the back buffer and the front buffer
		m_GraphicsAPI->m_pGraphicsAPIData->m_SwapChain->Present(0, 0);
	}

	void GraphicsUnitTest::MoveViewForward()
	{
		///The position where it will move.
		Vector4D pos = { m_View._m.m30, m_View._m.m31, m_View._m.m32, m_View._m.m33 };
		pos.Z -= 0.5f;
		m_View = m_View.Translate(pos);
	}

	void GraphicsUnitTest::MoveViewBack()
	{
		///The position where it will move.
		Vector4D pos = { m_View._m.m30, m_View._m.m31, m_View._m.m32, m_View._m.m33 };
		pos.Z += 0.5f;
		m_View = m_View.Translate(pos);
	}

	void GraphicsUnitTest::MoveViewLeft()
	{
		///The position where it will move.
		Vector4D pos = { m_View._m.m30, m_View._m.m31, m_View._m.m32, m_View._m.m33 };
		pos.X += 0.1f;
		m_View = m_View.Translate(pos);
	}

	void GraphicsUnitTest::MoveViewRight()
	{
		///The position where it will move.
		Vector4D pos = { m_View._m.m30, m_View._m.m31, m_View._m.m32, m_View._m.m33 };
		pos.X -= 0.1f;
		m_View = m_View.Translate(pos);
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
