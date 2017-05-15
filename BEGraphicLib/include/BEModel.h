#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BEVertexBuffer.h"
#include "BEIndexBuffer.h"

namespace BlackEngine
{
	struct GraphicsAPIData;

	class BE_GRAPHICS_EXPORT BEModel
	{
	public:
		BEModel();
		~BEModel();

		void Initialize();
		void Destroy();

		///carga el modelo.
		bool LoadModel(const String& pFile);
		///crea el buffer de vertices y de indices.
		bool CreateBuffers(const GraphicsAPIData * pGraphicData);
		///setea los buffers de vertices e indices.
		void SetBuffers(const GraphicsAPIData * pGraphicData);
		///regresa cuantos indices tiene el mesh seleccionado dentro del modelo.
		//uint32 GetIndicesSize(int32 wichMesh) { return m_Meshes[wichMesh].m_IB.GetIndicesSize(); }
		///Rendereamos todos los meshes
		void Render(const GraphicsAPIData * pGraphicData);

	private:
		//Vector<BEMesh> m_Meshes;
		Vector<BEVertexBuffer> m_VBVector;
		Vector<BEIndexBuffer> m_IBVector;
		//BEVertexBuffer m_VB;
		//BEIndexBuffer m_IB;
		void CreateVB(const GraphicsAPIData * pGraphicData);
		void SetVB(const GraphicsAPIData * pGraphicData);
		void CreateIB(const GraphicsAPIData * pGraphicData);
		void SetIB(const GraphicsAPIData * pGraphicData);
		//array de materiales
	};
}