#include "BERenderManager.h"
#include <BEGraphicsAPI.h>

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

	BERenderManager::BERenderManager()
	{
		m_BNeverChanges = nullptr;
		m_BChangeOnResize = nullptr;
		m_BChangesEveryFrame = nullptr;
	}

	BERenderManager::~BERenderManager()
	{
		Destroy();
	}

	void BERenderManager::Initialize()
	{
		Destroy();

		///constant buffers.
		m_BNeverChanges = new BEConstantBuffer();
		m_BChangeOnResize = new BEConstantBuffer();
		m_BChangesEveryFrame = new BEConstantBuffer();

		CreateVertexAndPixelShader();

		g_GraphicsAPI().m_pGraphicsAPIData->m_IL->CreateInputLayout(&m_GBufferVS);

		m_BNeverChanges->CreateBuffer();
		m_BChangeOnResize->CreateBuffer();
		m_BChangesEveryFrame->CreateBuffer();
		/// Create the sample state
		m_ColorSampler.Create();

		m_RasterizerState.Create();
	}

	void BERenderManager::Destroy()
	{
		if (m_BNeverChanges != nullptr)
		{
			m_BNeverChanges->Destroy();
			delete m_BNeverChanges;
			m_BNeverChanges = nullptr;
		}

		if (m_BChangeOnResize != nullptr)
		{
			m_BChangeOnResize->Destroy();
			delete m_BChangeOnResize;
			m_BChangeOnResize = nullptr;
		}

		if (m_BChangesEveryFrame != nullptr)
		{
			m_BChangesEveryFrame->Destroy();
			delete m_BChangesEveryFrame;
			m_BChangesEveryFrame = nullptr;
		}
	}

	void BERenderManager::Render(BEModel* ModelToRender, const BECamera& Camera, BEActor Actor)
	{
		Vector4D MeshColor;
		MeshColor.X = 0.7f;
		MeshColor.Y = 0.7f;
		MeshColor.Z = 0.7f;
		MeshColor.W = 1.0f;

		//TODO: hacer que ni el RTV ni el DSV dependan de graphics api.
		///limpiamos el back buffer.
		Vector4D CleanUpColor = { 0.0f, 0.125f, 0.3f, 1.0f };
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->ClearRenderTargetView(
			g_GraphicsAPI().GetRTV()->m_RenderTargetView, &CleanUpColor.X);

		///limpiamos el depth buffer.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->ClearDepthStencilView(
			g_GraphicsAPI().GetDSV()->m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		CBNeverChanges cbNeverChanges;
		cbNeverChanges.m_View = Camera.GetViewMatrix();
		cbNeverChanges.m_View.Transpose();
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BNeverChanges->m_BufferData->m_Buffer, 0, NULL, &cbNeverChanges, 0, 0);

		CBChangeOnResize cbChangesOnResize;
		cbChangesOnResize.m_Projection = Camera.GetProjectionMatrix();
		cbChangesOnResize.m_Projection.Transpose();
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BChangeOnResize->m_BufferData->m_Buffer, 0, NULL, &cbChangesOnResize, 0, 0);

		///variables que cambian cada frame
		CBChangesEveryFrame cb;
		cb.m_World = cb.m_World.Identity();
		cb.m_MeshColor = MeshColor;
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BChangesEveryFrame->m_BufferData->m_Buffer, 0, NULL, &cb, 0, 0);

		///seteo el vertex shader.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader
		(m_GBufferVS.m_VSData->m_VertexShader, NULL, 0);

		///se setean los constant buffers.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(0, 1, &m_BNeverChanges->m_BufferData->m_Buffer);

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(1, 1, &m_BChangeOnResize->m_BufferData->m_Buffer);

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(2, 1, &m_BChangesEveryFrame->m_BufferData->m_Buffer);

		///se setea el pixel shader.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetShader
		(m_GBufferPS.m_PSData->m_PixelShader, NULL, 0);
		///se setean los samplers.

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetSamplers
		(0, 1, &m_ColorSampler.m_SD->m_samplerState);

		///mando el render de los modelos.
		ModelToRender->Render();

		///switch the back buffer and the front buffer
		g_GraphicsAPI().m_pGraphicsAPIData->m_SwapChain->Present(0, 0);
	}

	bool BERenderManager::CreateVertexAndPixelShader()
	{
		if (!m_GBufferVS.CreateShader("Resources\\Shaders\\GBuffer_VS.hlsl", "vs_5_0", "vs_main"))
		{
			std::cout << "no se pudo crear VS" << std::endl;
		}
		if (!m_GBufferPS.CreateShader("Resources\\Shaders\\GBuffer_PS.hlsl", "ps_5_0", "ps_main"))
		{
			std::cout << "no se puedo crear PS" << std::endl;
		}

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader(m_GBufferVS.m_VSData->m_VertexShader, 0, 0);
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetShader(m_GBufferPS.m_PSData->m_PixelShader, 0, 0);

		return true;
	}
}