#pragma once
#include <BERenderManager.h>
#include <BEApplication.h>
#include <Matrix4D.h>
#include <BECamera.h>

///The engine's namespace.
namespace BlackEngine
{
	///Forward Declarions
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

	///A class to test the graphic api, it inherits from application, making it one as well.
	///This means it creates a window and handles itself.
	class GraphicsUnitTest : public BEApplication
	{
	public:
		///Default constructor and destructor.
		GraphicsUnitTest();
		~GraphicsUnitTest();

		///Override the on initialize, this means anything that we initialize on that function
		///will be called right before finishing the parent's Initialize function.
		virtual void OnInitialize() override;
		///Updates every frame.
		virtual void OnUpdate(float delta) override;
		///Calls  all functions needed to render a 3D object in a tridimentional space.
		virtual void OnRender() override;

		///World, view, and projection matrices.
		Matrix4D m_World;
		Vector4D m_MeshColor;

		///Constant buffers.
		BEConstantBuffer* m_BNeverChanges;
		BEConstantBuffer* m_BChangeOnResize;
		BEConstantBuffer* m_BChangesEveryFrame;

	private:
		///This function returns true if it managed to succesfully create
		///both vertex, and pixel shader. Otherwise, it will return false.
		bool CreatePixelAndVertexShader();

		BERenderManager m_RM;

		///The Engine's Vertex Shader class
		BEVertexShader* m_VS;
		///The Engine's Pixel Shader class
		BEPixelShader* m_PS;
		///Vector that stores the different render target views.
		Vector<BERenderTargetView> m_RtvVector;
		///This variable is used to create a sampler state.
		BESampler* m_ColorSampler;
		///Used to create the rasterizer state.
		BERasterizerState* m_RasterizerState;
		///A vector were all the resources are stored.
		Vector<BEResource*> m_ResourceVector;
		///The camera that will be used.
		BECamera* m_Camera;
	};
}
