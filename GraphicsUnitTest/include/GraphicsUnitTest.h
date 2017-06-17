#pragma once
#include <BEApplication.h>
#include <Matrix4D.h>

namespace BlackEngine
{
	class BEConstantBuffer;
	class BESampler;
	class BEModel;
	class BEPixelShader;
	class BEVertexShader;
	class BETexture;
	class BEShaderResourceView;
	class BERasterizerState;
	class BEResource;
	class BETextureResource;
	class BEModelResource;
	class BERenderTargetView;

	class GraphicsUnitTest : public BEApplication
	{
	public:
		GraphicsUnitTest();
		~GraphicsUnitTest();

		virtual void OnInitialize() override;
		virtual void Update(float delta) override;
		virtual void Render() override;

		Matrix4D m_World;
		Matrix4D m_View;
		Matrix4D m_Projection;
		Vector4D m_MeshColor;

		BEConstantBuffer* m_BNeverChanges;
		BEConstantBuffer* m_BChangeOnResize;
		BEConstantBuffer* m_BChangesEveryFrame;

		BEModel* m_Model;

	private:
		///This function returns true if it managed to succesfully create
		///both vertex, and pixel shader. Otherwise, it will return false.
		bool CreatePixelAndVertexShader();

		///The Engine's Vertex Shader class
		BEVertexShader* m_VS;
		///The Engine's Pixel Shader class
		BEPixelShader* m_PS;
		///vector que almacena los diferentes render target views.
		Vector<BERenderTargetView> m_RtvVector;
		BESampler* m_ColorSampler;
		BERasterizerState* m_RasterizerState;

		Vector<BEResource*> m_ResourceVector;
	};
}
