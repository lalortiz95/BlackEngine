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
	class BEResourceManager;
	class BEResource;
	class BETextureResource;
	class BEModelResource;

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
		bool CreatePixelAndVertexShader();

		BEVertexShader* m_VS;
		BEPixelShader* m_PS;
		//BEShaderResourceView* m_ColorMap;
		BESampler* m_ColorSampler;
		BERasterizerState* m_RasterizerState;
		BEResourceManager* m_ResourceManager;

		//TODO: cambiar todo lo del vector de recursos y usar el resource manager
		///Almacenará los recursos que se carguen.
		//BEResource* m_Resource;
		//BETextureResource*  m_TextureResources;
		//BEModelResource* m_ModelResources;
		Vector<BEResource*> m_ResourceVector;
		///mapa donde almaceno todos los recursos, el int32 es el ID, y el recurso, puede ser
		///textura o modelo.
		//Map<String, BEResource*> m_ResourcesMap;
	};
}
