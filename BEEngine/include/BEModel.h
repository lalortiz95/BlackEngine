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
		bool LoadModel(const String& pFile);
		///crea el buffer de vertices y de indices.
		bool CreateBuffers();
		///setea los buffers de vertices e indices.
		void SetBuffers();
		///del string que nos da el material que cargamos del modelo, obtenemos el nombre
		///del archivo. Después lo cambiamos para que tenga la ruta necesaria para que carge
		///la textura.
		void SetTextureName(String& TextureFromMaterial);

		///regresa cuantos indices tiene el mesh seleccionado dentro del modelo.
		uint32 GetIndicesSize(int32 wichMesh) { return m_Meshes[wichMesh].m_IB.GetIndicesSize(); }
		///Rendereamos todos los meshes
		void Render();

	private:
		Vector<BEMesh> m_Meshes;

		void CreateVB();
		void SetVB();
		void CreateIB();
		void SetIB();
	};
}