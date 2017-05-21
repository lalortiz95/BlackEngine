#include "BEModelResource.h"
#include "BEParser.h"

#include <BEGraphicsAPI.h>
#include <BEModel.h>

namespace BlackEngine
{
	BEModelResource::BEModelResource()
	{
		m_Model = nullptr;
	}


	BEModelResource::~BEModelResource()
	{
		Destroy();
	}

	void BEModelResource::Load(const String& fileAddr)
	{
		//TODO: corregir esto, me lo está parseando mal, no entiendo por que.
		//BEParser parser;
		//Vector<String> FileName;
		//FileName = parser.ParseToStr(fileAddr, "\\", 0);
		//m_model->loadmodel(filename[filename.size() - 1]);

		m_Model->LoadModel(fileAddr, m_GA->m_pGraphicsAPIData);
		///carga los buffers de vertices y de indices.
		m_Model->CreateBuffers(m_GA->m_pGraphicsAPIData);
	}

	void BEModelResource::Initialize()
	{
		Destroy();
		m_Model = new BEModel();
		m_Model->Initialize();
	}

	void BEModelResource::Destroy()
	{
		if (m_Model != nullptr)
		{
			m_Model->Destroy();
		}
	}
}