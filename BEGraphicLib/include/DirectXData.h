#pragma once
#include <Vector4D.h>
#include <Vector3D.h>
#include <Vector2D.h>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>

//#include <Directxmathmatrix.inl>
//#include <xnamath.h>
namespace BlackEngine
{
	class BEVertexBuffer;
	class BEIndexBuffer;
	class BEInputLayout;

	struct BufferData
	{
		ID3D11Buffer* m_Buffer;
		BufferData()
		{
			m_Buffer = nullptr;
		}

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
		ID3D11Texture2D* m_Texture2D;


		TextureData()
		{
			m_Texture2D = nullptr;
		}

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
		ID3D11InputLayout* m_InputLayout;

		InputLayoutData()
		{
			m_InputLayout = nullptr;
		}

		void Destroy();
	};

	struct ShaderData
	{
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
			m_RenderTargetView->Release();
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
		BEInputLayout* m_IL;

		GraphicsAPIData()
		{
			m_Device = nullptr;
			m_DeviceContext = nullptr;
			m_SwapChain = nullptr;
			m_ShaderData = nullptr;
			m_VB = nullptr;
			m_IB = nullptr;
			m_IL = nullptr;
		}

		void Initialize();
		void Destroy();
	};
}