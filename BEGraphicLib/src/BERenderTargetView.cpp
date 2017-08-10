#include "BERenderTargetView.h"
#include "DirectXData.h"
#include "BETexture.h"
#include "Vector4D.h"

namespace BlackEngine
{

	BERenderTargetView::BERenderTargetView()
	{
		m_RTVData = nullptr;
	}

	BERenderTargetView::~BERenderTargetView()
	{
		Destroy();
	}

	void BERenderTargetView::Initialize()
	{
		Destroy();
		m_RTVData = new RTVData();
	}

	void BERenderTargetView::Destroy()
	{
		if (m_RTVData != nullptr)
		{
			m_RTVData->Destroy();
			delete m_RTVData;
			m_RTVData = nullptr;
		}
	}

	void BERenderTargetView::Clear(Vector4D cleanUpColor, const GraphicsAPIData * pGraphicData)
	{
		pGraphicData->m_DeviceContext->ClearRenderTargetView(
			m_RTVData->m_RenderTargetView, &cleanUpColor.X);
	}

	bool BERenderTargetView::Create(BETexture * texture, const GraphicsAPIData * pGraphicData)
	{
		///create our render target.
		HRESULT hr;
		hr = pGraphicData->m_Device->CreateRenderTargetView(
			texture->m_TextureData->m_Texture2D,
			NULL, &m_RTVData->m_RenderTargetView);

		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}

}
