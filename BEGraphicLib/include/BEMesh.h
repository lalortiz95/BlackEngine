#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BEVertexBuffer.h"
#include "BEIndexBuffer.h"

namespace BlackEngine
{
	class BE_GRAPHICS_EXPORT BEMesh
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