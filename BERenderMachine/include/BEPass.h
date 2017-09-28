#pragma once
#include "BEPrerequisitesRenderMachine.h"
#include <BEPixelShader.h>
#include <BEVertexShader.h>
#include <BERenderTargetView.h>
#include <BETexture.h>

namespace BlackEngine
{
	class BE_RENDERMACHINE_EXPORT BEPass
	{
	public:
		BEPass();
		~BEPass();

		/// 
		void Init();
		/// 
		void Destroy();

		/// Sets the textures, render targets, and shaders. Afterwards it draws.
		void StartPass();
		/// removes the render targets and textures from the pipeline.
		void EndPass();

	private:
		bool CreatePixelAndVertexShader();
		bool CreateTextures();
		bool CreateRenderTargets();
		
		/// Input textures for the pass.
		BETexture* m_InputTextures;
		/// The pass' render target views
		BERenderTargetView* m_RTV;
		/// The pass' pixel and vertex shader.
		BEPixelShader m_PixelShader;
		BEVertexShader m_VertexShader;
	};
}
