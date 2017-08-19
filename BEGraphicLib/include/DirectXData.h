#pragma once
#include <Vector4D.h>
#include <Vector3D.h>
#include <Vector2D.h>

///This headers check if the engine is being runed in a windows operative
///sysetm, and if so, it fill it's API variables with DirectX variables.
#ifdef BE_PLATFORM_WIN32
#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	class BEVertexBuffer;
	class BEIndexBuffer;
	class BEInputLayout;

	///Structs that hides the directx variables with one of our own.
	struct BufferData
	{
		///Directx buffer.
		ID3D11Buffer* m_Buffer;
		///Default constructor.
		BufferData()
		{
			m_Buffer = nullptr;
		}
		///Releses memory
		void Destroy()
		{
			if (m_Buffer != nullptr)
			{
				m_Buffer->Release();
				m_Buffer = nullptr;
			}
		}
	};

	struct TextureData
	{
		///Directx texture2D.
		ID3D11Texture2D* m_Texture2D;

		///Default constructor.
		TextureData()
		{
			m_Texture2D = nullptr;
		}

		///Releases the memory.
		void Destroy()
		{
			if (m_Texture2D != nullptr)
			{
				m_Texture2D->Release();
			}
		}
	};

	struct InputLayoutData
	{
		///Directx Input Layout.
		ID3D11InputLayout* m_InputLayout;

		///Default constructor.
		InputLayoutData()
		{
			m_InputLayout = nullptr;
		}

		void Destroy();
	};

	struct ShaderData
	{
		///Directx blob.
		ID3DBlob* m_Blob;

		ShaderData()
		{
			m_Blob = nullptr;
		}

		void Destroy()
		{
			if (m_Blob != nullptr)
			{
				m_Blob->Release();
				m_Blob = nullptr;
			}
		}
	};

	struct ShaderResourceViewData
	{
		ID3D11ShaderResourceView* m_SRV;

		ShaderResourceViewData()
		{
			m_SRV = nullptr;
		}

		void Destroy()
		{
			m_SRV->Release();
			m_SRV = nullptr;
		}
	};

	struct RasterizerStateData
	{
		ID3D11RasterizerState* m_RS;
		RasterizerStateData()
		{
			m_RS = nullptr;
		}

		void Destroy()
		{
			m_RS->Release();
		}

	};

	struct VertexShaderData
	{
		ID3D11VertexShader* m_VertexShader;

		VertexShaderData()
		{
			m_VertexShader = nullptr;
		}

		void Destroy()
		{
			m_VertexShader->Release();
		}
	};

	struct PixelShaderData
	{
		ID3D11PixelShader* m_PixelShader;

		PixelShaderData()
		{
			m_PixelShader = nullptr;
		}

		void Destroy()
		{
			m_PixelShader->Release();
		}
	};

	struct DSVData
	{
		ID3D11DepthStencilView* m_DepthStencilView;

		DSVData()
		{
			m_DepthStencilView = nullptr;
		}

		void Destroy()
		{
			m_DepthStencilView->Release();
		}
	};

	struct RTVData
	{
		ID3D11RenderTargetView* m_RenderTargetView;

		RTVData()
		{
			m_RenderTargetView = nullptr;
		}

		void Destroy()
		{
			if (m_RenderTargetView != nullptr)
			{
				m_RenderTargetView->Release();
			}
		}
	};

	struct SamplerData
	{
		ID3D11SamplerState* m_samplerState;

		SamplerData()
		{
			m_samplerState = nullptr;
		}

		void Destroy()
		{
			m_samplerState->Release();
		}
	};

	struct GraphicsAPIData
	{
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
		IDXGISwapChain* m_SwapChain;
		ShaderData* m_ShaderData;
		BEVertexBuffer* m_VB;
		BEIndexBuffer* m_IB;

		GraphicsAPIData()
		{
			m_Device = nullptr;
			m_DeviceContext = nullptr;
			m_SwapChain = nullptr;
			m_ShaderData = nullptr;
			m_VB = nullptr;
			m_IB = nullptr;
		}

		void Initialize();
		void Destroy();
	};
}
#endif // BE_PLATFORM_WIN32