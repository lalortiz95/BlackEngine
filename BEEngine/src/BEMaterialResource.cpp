#include "BEMaterialResource.h"

namespace BlackEngine
{
	BEMaterialResource::BEMaterialResource()
	{
		m_Material = nullptr;
	}

	BEMaterialResource::~BEMaterialResource()
	{
		Destroy();
	}

	void BEMaterialResource::Load(const String & fileName)
	{
		
	}

	void BEMaterialResource::Initialize()
	{
		///limpio la memoria.
		Destroy();
		///le asigno memoria e inicializo al material.
		m_Material = new BEMaterial();
		m_Material->Initialize();
	}

	void BEMaterialResource::Destroy()
	{
		if (m_Material != nullptr)
		{
			m_Material->Destroy();
			delete m_Material;
			m_Material = nullptr;
		}
	}
}