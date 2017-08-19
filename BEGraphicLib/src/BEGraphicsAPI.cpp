#include "BEGraphicsAPI.h"

#include "DirectXData.h"
#include "BETexture.h"
#include "BEVertexBuffer.h"
#include "BEIndexBuffer.h"
#include "BEVertexShader.h"
#include "BEPixelShader.h"
#include "BEInputLayout.h"
#include "BERenderTargetView.h"
#include "BEDepthStencilView.h"

#include <Vector4D.h>

namespace BlackEngine
{
	BEGraphicsAPI::BEGraphicsAPI(void* screenHandle, int32 width, int32 height,
		bool fullscreen, int32 format, int32 backBufferCount, bool vSync)
	{
		///Copiamos localmente las variables de inicializacion
		m_screenHandle = screenHandle;
		m_width = width;
		m_height = height;
		m_fullscreen = fullscreen;
		m_format = format;
		m_backBufferCount = backBufferCount;
		m_vSync = vSync;

		m_pGraphicsAPIData = nullptr;
		m_pGraphicsAPIData = nullptr;
	}

	BEGraphicsAPI::~BEGraphicsAPI()
	{
		Destroy();
	}

	void BEGraphicsAPI::OnStartUp(void * screenHandle, int32 width, int32 height, bool fullscreen, int32 format, int32 backBufferCount, bool vSync)
	{
		///Copiamos localmente las variables de inicializacion
		m_screenHandle = screenHandle;
		m_width = width;
		m_height = height;
		m_fullscreen = fullscreen;
		m_format = format;
		m_backBufferCount = backBufferCount;
		m_vSync = vSync;

		m_pGraphicsAPIData = nullptr;
		m_pGraphicsAPIData = nullptr;
	}

	void BEGraphicsAPI::OnShutDown()
	{
		Destroy();
	}

	void BEGraphicsAPI::Destroy()
	{
		if (m_pGraphicsAPIData != nullptr)
		{
			m_pGraphicsAPIData->Destroy();
			m_pGraphicsAPIData = nullptr;
		}

		m_backBufferCount = 0;
		m_height = 0;
		m_width = 0;
	}

	void BEGraphicsAPI::ClearBackBuffer(BERenderTargetView& RTV, float r, float g, float b, float a)
	{
		Vector4D color(r, g, b, a);
		m_pGraphicsAPIData->m_DeviceContext->ClearRenderTargetView(
			RTV.m_RTVData->m_RenderTargetView, &color.X);
	}

	bool BEGraphicsAPI::Initialize(void* scrHandle, int32 width, int32 height, int32 numBB, bool isFullScr)
	{
		Destroy();

		///asigno memoria
		m_pGraphicsAPIData = new GraphicsAPIData();
		m_pGraphicsAPIData->Initialize();

		///inicializamos variables miembras 
		m_width = width;
		m_height = height;
		m_screenHandle = scrHandle;
		m_backBufferCount = numBB;
		m_fullscreen = isFullScr;

		///se asigna un device.
		InitDevice();
		///creamos el device context, que es la manera de comunicarnos con el hardware
		InitDeviceContext();
		///el swap chain cambia entre los back buffers y el front buffer
		CreateSwapChain();

		///seteamos el view port.
		SetViewPort();
		///limpiamos los pixeles almacenados en el back buffer.
		//ClearBackBuffer();

		return true;
	}

	void BEGraphicsAPI::InitDevice()
	{
	}

	void BEGraphicsAPI::InitDeviceContext()
	{
	}

	void BEGraphicsAPI::CreateSwapChain()
	{
		//Describe our SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc;

		//Describe our Buffer
		DXGI_MODE_DESC bufferDesc;

		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = m_width;
		bufferDesc.Height = m_height;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = reinterpret_cast<HWND>(m_screenHandle);
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		uint32 flags = 0;
#if BE_DEBUG_MODE
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		//Create our SwapChain
		HRESULT hres = D3D11CreateDeviceAndSwapChain
		(
			NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, NULL, NULL,
			D3D11_SDK_VERSION, &swapChainDesc, &m_pGraphicsAPIData->m_SwapChain,
			&m_pGraphicsAPIData->m_Device, NULL, &m_pGraphicsAPIData->m_DeviceContext
		);

		if (FAILED(hres))
		{
			return;
		}
	}

	void BEGraphicsAPI::LinkDepthStencil()
	{
		
	}

	void BEGraphicsAPI::SetRenderTargetAndDepthStencil(BERenderTargetView* RTV, BEDepthStencilView* DSV)
	{
		ID3D11DepthStencilView* pDepthStencilView = DSV->m_DSVData->m_DepthStencilView;
		ID3D11RenderTargetView* pRenderTargetView = RTV->m_RTVData->m_RenderTargetView;

		///Set our Render Target	
		m_pGraphicsAPIData->m_DeviceContext->OMSetRenderTargets(1,
			&pRenderTargetView, pDepthStencilView);
	}

	bool BEGraphicsAPI::CreateDepthStencilView(BETexture *Texture, BEDepthStencilView* DSV)
	{
		if (!Texture->CreateTexture(m_width, m_height,TEXTURE_CREATION::kDepthStencil))
		{
			return false;
		}

		ID3D11Resource* pResource = Texture->m_TextureData->m_Texture2D;

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		HRESULT Hres = m_pGraphicsAPIData->m_Device->CreateDepthStencilView(pResource, &descDSV,
			&DSV->m_DSVData->m_DepthStencilView);

		if (Hres == S_OK)
		{
			return true;
		}
		return false;
	}

	VertexShaderData * BEGraphicsAPI::GetVS()
	{
		return m_VS->m_VSData;
	}

	PixelShaderData * BEGraphicsAPI::GetPS()
	{
		return m_PS->m_PSData;
	}

	void BEGraphicsAPI::SetViewPort()
	{
		D3D11_VIEWPORT vp;

		vp.Width = (float)m_width;
		vp.Height = (float)m_height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		m_pGraphicsAPIData->m_DeviceContext->RSSetViewports(1, &vp);
	}

	BE_GRAPHICS_EXPORT BEGraphicsAPI & g_GraphicsAPI()
	{
		return BEGraphicsAPI::Instance();
	}
}