#pragma once
#include "BEPrerequisitesRenderMachine.h"
#include <BERenderTargetView.h>
#include <BEDepthStencilView.h>
#include <BERasterizerState.h>
#include <BEConstantBuffer.h>
#include <BEVertexShader.h>
#include <BEPixelShader.h>
#include <BEInputLayout.h>
#include <BETexture.h>
#include <BESampler.h>
#include <BECamera.h>
#include <BEModel.h>
#include <BELight.h>

#include "BEPass.h"

namespace BlackEngine
{
	struct BEActor
	{
		Vector3D Position;
		Vector3D Rotation;
		Vector3D Scale;
	};

	class BE_RENDERMACHINE_EXPORT BERenderManager
	{
	public:
		BERenderManager();
		~BERenderManager();

		void Initialize();
		void Destroy();

		void Render(BEModel* ModelToRender, const BECamera& Camera, BEActor Actor);

		/// Salida de g buffer, position, normal, color, physics.
		BERenderTargetView m_GBuffer[4];
		/// Salida del Ambien Occlusion.
		BERenderTargetView m_SSAO;
		/// Salida del blur
		BERenderTargetView m_Blur;
		///
		BERenderTargetView m_MidPoint;
		///
		BERenderTargetView m_Luminance;
		///
		BERenderTargetView m_Brightness;

		///Constant buffers.
		BEConstantBuffer* m_BNeverChanges;
		BEConstantBuffer* m_BChangeOnResize;
		BEConstantBuffer* m_BChangesEveryFrame;

		BEConstantBuffer m_LightBuffer;

		/// The shaders needed for the GBuffer.
		BEVertexShader m_GBufferVS;
		BEPixelShader m_GBufferPS;

		BEDepthStencilView m_DSV;
		BERenderTargetView m_RTV;

		BETexture m_BackBuffer;
		BETexture m_DSVTexture;

		/// 
		BESampler m_ColorSampler;

		/// the rasterizer state.
		BERasterizerState m_RasterizerState;

		/// The input layout.
		BEInputLayout m_InputLayout;
	private:
		bool CreateVertexAndPixelShader();
	};
}