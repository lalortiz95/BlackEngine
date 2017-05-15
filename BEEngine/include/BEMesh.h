#pragma once
#include "BEPrerequisitesEngine.h"
#include <BEVertexBuffer.h>
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
	};
}