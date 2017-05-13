#include "BEMaterial.h"

#include <BEResource.h>

namespace BlackEngine
{
	BEMaterial::BEMaterial()
	{
		m_Diffuse = nullptr;
	}

	BEMaterial::~BEMaterial()
	{
		Destroy();
	}

	void BEMaterial::Initialize()
	{

	}

	void BEMaterial::Destroy()
	{
		if (m_Diffuse != nullptr)
		{
			m_Diffuse->Destroy();
			m_Diffuse = nullptr;
		}
	}
}