#include "BEMaterial.h"

#include "BEResource.h"
#include "BETextureResource.h"
#include "BEShaderResourceView.h"

namespace BlackEngine
{
	BEMaterial::BEMaterial()
	{
		for (auto& iter : m_Textures)
		{
			iter = nullptr;
		}
	}

	BEMaterial::~BEMaterial()
	{
		Destroy();
	}

	void BEMaterial::Initialize()
	{
		//TODO: corregir esto, supongo...
		for (SIZE_T i = 0; i < aiTextureType_UNKNOWN; ++i)
		{
			m_Textures[i] = new BEShaderResourceView();
			m_Textures[i]->Initialize();
		}
	}

	void BEMaterial::Destroy()
	{
		for (auto& iter : m_Textures)
		{
			if (iter)
			{
				iter->Destroy();
				delete iter;
				iter = NULL;
			}
		}
	}
}