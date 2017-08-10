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
#include <Quaternion.h>

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include <BEResourceManager.h>

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
		///Inicializacion de modulos sistema
		g_ResourceManager().StartUp();
		g_ResourceManager().Initialize();
		//g_ResourceManager().m_GA = m_GraphicsAPI;

		m_ColorSampler = new BESampler();

		///constant buffers.
		m_BNeverChanges = new BEConstantBuffer();
		m_BChangeOnResize = new BEConstantBuffer();
		m_BChangesEveryFrame = new BEConstantBuffer();
		m_RasterizerState = new BERasterizerState();

		m_MeshColor.X = 0.7f;
		m_MeshColor.Y = 0.7f;
		m_MeshColor.Z = 0.7f;
		m_MeshColor.W = 1.0f;

		if (!CreatePixelAndVertexShader())
		{
			//Ayudaaaa
		}

		///creamos y seteamos el vertex buffer.
		g_GraphicsAPI().m_pGraphicsAPIData->m_IL->CreateInputLayout(m_VS);

		///cargo los recursos y los introduzco en el vector.
		m_ResourceVector.push_back(g_ResourceManager().LoadResourceFromFile("Resources\\Models\\samus.fbx"));

		/// select which primtive type we are using
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->IASetPrimitiveTopology
		(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);

		if (!m_BNeverChanges->CreateBuffer(g_GraphicsAPI().m_pGraphicsAPIData))
		{
			//cámara no funciono.
		}
		m_BChangeOnResize->CreateBuffer(g_GraphicsAPI().m_pGraphicsAPIData);
		m_BChangesEveryFrame->CreateBuffer(g_GraphicsAPI().m_pGraphicsAPIData);

		/// Create the sample state
		m_ColorSampler->Create(g_GraphicsAPI().m_pGraphicsAPIData);

		///creamos el rasterizer state.
		m_RasterizerState->Create(g_GraphicsAPI().m_pGraphicsAPIData);

		m_World = m_World.Identity();

		Matrix4D M;
		///inicializamos la matriz de vista.
		Vector4D Eye(5.0f, 5.0f, -15.0f, 0.0f);
		Vector4D At(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4D Up(0.0f, 1.0f, 0.0f, 0.0f);
		///Asignamos memoria a la cámara, con el eye, el target, y su up definidos.
		m_Camera = new BECamera(Eye, At, Up);
		///Seteamos la matriz de vista.
		m_Camera->SetViewMatrix(M.LookAtLH(Eye, At, Up));

		///matriz de proyección.
		Matrix4D projMatrix = M.PerspectiveFOVLH(Math::QUARTER_PI, m_Width, m_Height, 0.01f, 100.0f);
		m_Camera->SetProjectionMatrix(projMatrix);

		//TEMP
		m_Camera->m_Speed = 10;
	}

	void GraphicsUnitTest::OnUpdate(float delta)
	{
		if (m_InputInterface.m_Keyboard.IsPressed(DIK_W))
		{
			///We calculate how many units per second the camera moves, with it's speed,
			///the time, and the dirección it's moving
			Vector4D tempPos(0, 0, 1, 0);
			tempPos *= delta * m_Camera->m_Speed;
			/// We move our camera.
			m_Camera->Move(tempPos);
		}
		if (m_InputInterface.m_Keyboard.IsPressed(DIK_S))
		{
			Vector4D tempPos(0, 0, -1, 0);
			tempPos *= delta * m_Camera->m_Speed;
			m_Camera->Move(tempPos);
		}
		if (m_InputInterface.m_Keyboard.IsPressed(DIK_A))
		{
			Vector4D tempPos(-1, 0, 0, 0);
			tempPos *= delta * m_Camera->m_Speed;
			m_Camera->Move(tempPos);
		}
		if (m_InputInterface.m_Keyboard.IsPressed(DIK_D))
		{
			Vector4D tempPos(1, 0, 0, 0);
			tempPos *= delta * m_Camera->m_Speed;
			m_Camera->Move(tempPos);
		}
		if (m_InputInterface.m_Keyboard.IsPressed(DIK_LSHIFT))
		{
			Vector4D tempPos(0, 1, 0, 0);
			tempPos *= delta * m_Camera->m_Speed;
			m_Camera->Move(tempPos);
		}
		if (m_InputInterface.m_Keyboard.IsPressed(DIK_LCONTROL))
		{
			Vector4D tempPos(0, -1, 0, 0);
			tempPos *= delta * m_Camera->m_Speed;
			m_Camera->Move(tempPos);
		}

		if (m_InputInterface.m_Mouse.IsPressed(0))
		{
			Vector3D tempAxis = { 0, 1, 0 };
			m_Camera->Rotate(tempAxis, (15.0f * Math::PI / 180.f));

			//TODO: usar quaternions para rotar, luego la noramlizamos, y por
			//último la convertimos a matriz.
		}

		m_Camera->Update(delta);

		//TODO: debuggear.
		Quaternion RotatedQuaternion;
		///Almaceno en un vector 4D los axis que recibe la función. 
		Vector3D anglesToRotate = { 0, 1, 0 };

		RotatedQuaternion.RotateLocal(anglesToRotate, (15.0f * Math::PI / 180.f));
		RotatedQuaternion.Normalize();
		Matrix4D RotationMatrix = RotatedQuaternion.ConvertToMatrix();

		//m_World *= RotationMatrix;
	}

	void GraphicsUnitTest::OnRender()
	{
		//esto es si queremos que tome la función render del padre.
		//__super::Render();

		///limpiamos el back buffer.
		Vector4D CleanUpColor = { 0.0f, 0.125f, 0.3f, 1.0f };
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->ClearRenderTargetView(
			g_GraphicsAPI().GetRTV()->m_RenderTargetView, &CleanUpColor.X);

		///limpiamos el depth buffer.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->ClearDepthStencilView(
			g_GraphicsAPI().GetDSV()->m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		CBNeverChanges cbNeverChanges;
		cbNeverChanges.m_View = m_Camera->GetViewMatrix();
		cbNeverChanges.m_View.Transpose();
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BNeverChanges->m_BufferData->m_Buffer, 0, NULL, &cbNeverChanges, 0, 0);

		CBChangeOnResize cbChangesOnResize;
		cbChangesOnResize.m_Projection = m_Camera->GetProjectionMatrix();
		cbChangesOnResize.m_Projection.Transpose();
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BChangeOnResize->m_BufferData->m_Buffer, 0, NULL, &cbChangesOnResize, 0, 0);

		///variables que cambian cada frame
		CBChangesEveryFrame cb;
		cb.m_World = m_World;
		cb.m_MeshColor = m_MeshColor;
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->UpdateSubresource(
			m_BChangesEveryFrame->m_BufferData->m_Buffer, 0, NULL, &cb, 0, 0);

		///seteo el vertex shader.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader
		(m_VS->m_VSData->m_VertexShader, NULL, 0);
		///se setean los constant buffers.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(0, 1, &m_BNeverChanges->m_BufferData->m_Buffer);

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(1, 1, &m_BChangeOnResize->m_BufferData->m_Buffer);

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetConstantBuffers
		(2, 1, &m_BChangesEveryFrame->m_BufferData->m_Buffer);
		///se setea el pixel shader.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetShader
		(m_PS->m_PSData->m_PixelShader, NULL, 0);
		///se setean los samplers.
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetSamplers
		(0, 1, &m_ColorSampler->m_SD->m_samplerState);

		///mando el render de los modelos.
		for (auto& res : m_ResourceVector)
		{
			if (res->GetResourceType() == RT_MODEL)
			{
				dynamic_cast<BEModelResource*>(res)->m_Model->Render(g_GraphicsAPI().m_pGraphicsAPIData);
			}
		}

		///switch the back buffer and the front buffer
		g_GraphicsAPI().m_pGraphicsAPIData->m_SwapChain->Present(0, 0);
	}

	bool GraphicsUnitTest::CreatePixelAndVertexShader()
	{
		m_VS = new BEVertexShader();
		m_PS = new BEPixelShader();

		if (!m_VS->CreateShader("Resources\\Shaders\\VertexShader.hlsl", "vs_5_0", "VSMain"))
		{
			std::cout << "no se pudo crear VS" << std::endl;
		}
		if (!m_PS->CreateShader("Resources\\Shaders\\PixelShader.hlsl", "ps_5_0", "PSMain"))
		{
			std::cout << "no se puedo crear PS" << std::endl;
		}

		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->VSSetShader(m_VS->m_VSData->m_VertexShader, 0, 0);
		g_GraphicsAPI().m_pGraphicsAPIData->m_DeviceContext->PSSetShader(m_PS->m_PSData->m_PixelShader, 0, 0);

		return true;
	}
}
