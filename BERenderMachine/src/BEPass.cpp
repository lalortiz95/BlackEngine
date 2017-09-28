#include "BEPass.h"

namespace BlackEngine
{
	BEPass::BEPass()
	{

	}

	BEPass::~BEPass()
	{

	}

	void BEPass::Init()
	{

	}

	void BEPass::Destroy()
	{

	}

	void BEPass::StartPass()
	{
		/// Se setean en el pipeline las texturas, los render targets, y los shaders.
		CreateTextures();
		CreateRenderTargets();
		CreatePixelAndVertexShader();
	}

	void BEPass::EndPass()
	{
		//TODO: remover los render targets y las texturas del pipeline.
	}

	bool BEPass::CreatePixelAndVertexShader()
	{
		if (!m_VertexShader.CreateShader("Resources\\Shaders\\VertexShader.hlsl", "vs_5_0", "VSMain"))
		{
			return false;
		}
		if (!m_PixelShader.CreateShader("Resources\\Shaders\\PixelShader.hlsl", "ps_5_0", "PSMain"))
		{
			return false;
		}

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader(m_VertexShader.m_VSData->m_VertexShader, 0, 0);
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetShader(m_PixelShader.m_PSData->m_PixelShader, 0, 0);

		return true;
	}

	bool BEPass::CreateTextures()
	{
		return false;
	}

	bool BEPass::CreateRenderTargets()
	{
		//m_RTV->Create();
		return false;
	}
}