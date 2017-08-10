#include "BEModelResource.h"
#include "BEParser.h"

#include <BEGraphicsAPI.h>
#include <BEModel.h>

namespace BlackEngine
{
	BEModelResource::BEModelResource()
	{
		m_Model = nullptr;
		Initialize();
	}


	BEModelResource::~BEModelResource()
	{
		Destroy();
	}

	void BEModelResource::Load(const String& fileName)
	{
		m_Model->LoadModel(fileName);
		///carga los buffers de vertices y de indices.
		m_Model->CreateBuffers();
	}

	void BEModelResource::Initialize()
	{
		Destroy();
		m_Model = new BEModel();
	}

	void BEModelResource::Destroy()
	{
		if (m_Model != nullptr)
		{
			m_Model->Destroy();
		}
	}
}