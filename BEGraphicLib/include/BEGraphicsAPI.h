#pragma once

#include "BEPrerequisitesGraphics.h"
#include "BEModule.h"
#include "BEVertex.h"
#include <BEMath.h>

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
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

	///Declaration of GraphicAPI class, that is also a module.
	class BE_GRAPHICS_EXPORT BEGraphicsAPI : public Module<BEGraphicsAPI>
	{
	public:
		///default constructor.
		BEGraphicsAPI() {};
		///constructor with parameters,
		BEGraphicsAPI(int32 screenHandle, int32 width, int32 height, bool fullscreen, int32 format, int32 backBufferCount, bool vSync);
		///Default destructor.
		virtual ~BEGraphicsAPI();

		///Functions to create and destroy de module.
		virtual void OnStartUp() override;
		virtual void OnShutDown() override;

		///Function that initializes the class' variables.
		bool Initialize(int32 scrHandle, int32 width, int32 height, int32 numBB, bool isFullScreen);
		///Clears the back buffer with a given color.
		void ClearBackBuffer(float r = 0, float g = 1.f, float b = 0, float a = 0);

		///Sets the render target, and the depth stencil view.
		void SetRenderTargetAndDepthStencil(BERenderTargetView*, BEDepthStencilView*);
		///The device creates a DSV.
		bool CreateDepthStencilView(BETexture*, BEDepthStencilView*&);
		///Returns the RTV, and DSV member variables.
		RTVData* GetRTV();
		DSVData* GetDSV();
		///Returns the vertex and pixel shader member variables.
		VertexShaderData* GetVS(); 
		PixelShaderData* GetPS();
		///Stores de graphicAPI data.
		GraphicsAPIData* m_pGraphicsAPIData;
	
	private:
		int32 m_screenHandle;
		int32 m_width;
		int32 m_height;
		///Flag that indicates if we are in fullscreen mode.
		bool m_fullscreen;
		int32 m_format;
		///amount of back buffers.
		int32 m_backBufferCount;
		///Flag that indicates if we are in fullscreen mode.
		bool m_vSync;

		BERenderTargetView* m_RTV;
		BEDepthStencilView* m_DSV;
		BETexture* m_BackBuffer;
		BETexture* m_DSVTexture;

		BEVertexShader* m_VS;
		BEPixelShader* m_PS;

		void Destroy();
		///Initializes the API's device.
		void InitDevice();
		///Initializes the API's device context.
		void InitDeviceContext();
		///Creates a Swap chain
		void CreateSwapChain();
		///Creates and links the depth stencil.
		void LinkDepthStencil();
		///Sets the viewport.
		void SetViewPort();
	};
}
