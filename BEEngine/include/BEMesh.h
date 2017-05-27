#pragma once
#include "BEPrerequisitesEngine.h"
#include <BEVertexBuffer.h>
#include "BEMaterial.h"

#include <BEIndexBuffer.h>

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BEMesh
	{
	public:
		BEMesh();
		~BEMesh();

		bool Initialize();
		void Destroy();

		BEVertexBuffer m_VB;
		BEIndexBuffer m_IB;
		BEMaterial m_Material;
	};
}