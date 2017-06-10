#pragma once

#include "BEPrerequisitesGraphics.h"
#include "BEModule.h"
#include "BEVertex.h"
#include <BEMath.h>

namespace BlackEngine
{
	class BETexture;
	class BERenderTargetView;
	class BEDepthStencilView;
	class BEVertexShader;
	class BEPixelShader;

	struct GraphicsAPIData;
	struct RTVData;
	struct DSVData;
	struct VertexShaderData;
	struct PixelShaderData;

	class BE_GRAPHICS_EXPORT BEGraphicsAPI : public Module<BEGraphicsAPI>
	{
	public:
		BEGraphicsAPI() {};
		BEGraphicsAPI(int32 screenHandle, int32 width, int32 height, bool fullscreen, int32 format, int32 backBufferCount, bool vSync);
		virtual ~BEGraphicsAPI();

		virtual void OnStartUp() override;
		virtual void OnShutDown() override;

		bool Initialize(int32 scrHandle, int32 width, int32 height, int32 numBB, bool isFullScreen);
		void ClearBackBuffer(float r = 0, float g = 1.f, float b = 0, float a = 0);

		//bool CreateRenderTargetView(BETexture*, BERenderTargetView*&);
		void SetRenderTargetAndDepthStencil(BERenderTargetView*, BEDepthStencilView*);
		bool CreateDepthStencilView(BETexture*, BEDepthStencilView*&);
		RTVData* GetRTV();
		DSVData* GetDSV();
		VertexShaderData* GetVS(); 
		PixelShaderData* GetPS();

		GraphicsAPIData* m_pGraphicsAPIData;
	private:
		int32 m_screenHandle;
		int32 m_width;
		int32 m_height;
		bool m_fullscreen;
		int32 m_format;
		int32 m_backBufferCount;
		bool m_vSync;

		BERenderTargetView* m_RTV;
		BEDepthStencilView* m_DSV;
		BETexture* m_BackBuffer;
		BETexture* m_DSVTexture;

		BEVertexShader* m_VS;
		BEPixelShader* m_PS;

		void Destroy();

		void InitDevice();
		void InitDeviceContext();
		void CreateSwapChain();
		void LinkDepthStencil();
		void SetViewPort();
	};
}
