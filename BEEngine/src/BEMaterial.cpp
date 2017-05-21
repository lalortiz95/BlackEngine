#include "BEMaterial.h"

#include "BEResource.h"
#include "BETextureResource.h"

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
		m_Diffuse = new BETextureResource();
		m_Diffuse->Initialize();
		m_Ambiental = new BETextureResource();
		m_Ambiental->Initialize();
		m_Emisive = new BETextureResource();
		m_Emisive->Initialize();
		m_Normal = new BETextureResource();
		m_Normal->Initialize();
		m_Specular = new BETextureResource();
		m_Specular->Initialize();
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