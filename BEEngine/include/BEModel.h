#pragma once
#include "BEPrerequisitesEngine.h"
#include "BEMesh.h"
#include "BEMaterial.h"

#include <BEVertexBuffer.h>
#include <BEIndexBuffer.h>

namespace BlackEngine
{
	struct GraphicsAPIData;

	class BE_ENGINE_EXPORT BEModel
	{
	public:
		BEModel();
		~BEModel();

		void Initialize();
		void Destroy();

		///carga el modelo.
		bool LoadModel(const String& pFile, const GraphicsAPIData * pGraphicData);
		///crea el buffer de vertices y de indices.
		bool CreateBuffers(const GraphicsAPIData * pGraphicData);
		///setea los buffers de vertices e indices.
		void SetBuffers(const GraphicsAPIData * pGraphicData);
		///del string que nos da el material que cargamos del modelo, obtenemos el nombre
		///del archivo. Despu�s lo cambiamos para que tenga la ruta necesaria para que carge
		///la textura.
		void SetTextureName(String& TextureFromMaterial);

		///regresa cuantos indices tiene el mesh seleccionado dentro del modelo.
		uint32 GetIndicesSize(int32 wichMesh) { return m_Meshes[wichMesh].m_IB.GetIndicesSize(); }
		///Rendereamos todos los meshes
		void Render(const GraphicsAPIData * pGraphicData);

	private:
		Vector<BEMesh> m_Meshes;

		void CreateVB(const GraphicsAPIData * pGraphicData);
		void SetVB(const GraphicsAPIData * pGraphicData);
		void CreateIB(const GraphicsAPIData * pGraphicData);
		void SetIB(const GraphicsAPIData * pGraphicData);
	};
}