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

		/// We initialize our input layout object.
		m_InputLayout.Initialize();
		m_DSV.Initialize();
		m_RTV.Initialize();
		m_BackBuffer.Initialize();
		m_DSVTexture.Initialize();
		m_LightBuffer.Initialize();

		//TODO: cambiar esto, puede setear uno u otro, y cuantos sean de cada uno.
		if (!m_GBufferVS.CreateShader("Resources\\Shaders\\GBuffer_VS.hlsl", "vs_5_0", "vs_main"))
		{
			throw std::exception("No se pudo crear VS");
		}
		if (!m_GBufferPS.CreateShader("Resources\\Shaders\\GBuffer_PS.hlsl", "ps_5_0", "ps_main"))
		{
			std::cout << "no se puedo crear PS" << std::endl;
		}

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader(m_GBufferVS.m_VSData->m_VertexShader, 0, 0);
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetShader(m_GBufferPS.m_PSData->m_PixelShader, 0, 0);

		///le pedimos al swap chain el buffer que queremos a  manera de textura
		g_GraphicsAPI().m_pGraphicsAPIData->m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			(void**)&m_BackBuffer.m_TextureData->m_Texture2D);

		//TODO: crear textura de render target.
		///creamos el render target view.
		m_RTV.Create(&m_BackBuffer);
		///creanos el depth stencil view.
		g_GraphicsAPI().CreateDepthStencilView(&m_DSVTexture, &m_DSV);
		//m_RTTexture.Initialize(*m_RTV);
		//m_RTTexture.CreateTextureFromFile();
		//m_RTTexture.CreateAsRenderTarget();
		///seteamos el render target view.
		g_GraphicsAPI().SetRenderTargetAndDepthStencil(&m_RTV, &m_DSV);

		/// Clear the back bufffer.
		g_GraphicsAPI().ClearBackBuffer(m_RTV);

		/// Create out input layout.
		m_InputLayout.CreateInputLayout(&m_GBufferVS);

		/// Create the constant buffers.
		m_BNeverChanges->CreateBuffer(sizeof(Matrix4D));
		m_BChangeOnResize->CreateBuffer(sizeof(Matrix4D));
		m_BChangesEveryFrame->CreateBuffer(sizeof(Matrix4D));

		/// Creates the light constant buffer.
		m_LightBuffer.CreateBuffer(40);

		/// Create the sample state
		m_ColorSampler.Create();
		/// Create the rasterizer state.
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

		///limpiamos el depth buffer.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->ClearDepthStencilView(
			m_DSV.m_DSVData->m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

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

		/// Set the light buffer.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_LightBuffer.m_BufferData->m_Buffer, 0, NULL, &m_LightBuffer, 0, 0);

		///seteo el vertex shader.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader
		(m_GBufferVS.m_VSData->m_VertexShader, NULL, 0);

		///Se setea  el input layout.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->IASetInputLayout(
			m_InputLayout.m_ILData->m_InputLayout);

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


		return true;
	}
}