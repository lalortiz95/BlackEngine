#include "BEMesh.h"
#include <BEIndexBuffer.h>
#include <BEVertexBuffer.h>

namespace BlackEngine
{
	BEMesh::BEMesh()
	{
	}

	BEMesh::~BEMesh()
	{
		Destroy();
	}

	bool BEMesh::Initialize()
	{
		m_VB.Initialize();
		m_IB.Initialize();
		return true;
	}

	void BEMesh::Destroy()
	{
		m_IB.Destroy();
		m_VB.Destroy();
	}
}