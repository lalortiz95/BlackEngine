#include "BETextureResource.h"

#include <BEModule.h>
#include <BETexture.h>
#include <BEGraphicsAPI.h>
#include <BEGraphicsAPI.h>

namespace BlackEngine
{
	BETextureResource::BETextureResource()
	{
		m_Texture = nullptr;
	}

	BETextureResource::~BETextureResource()
	{
		Destroy();
	}

	void BETextureResource::Load(const String& fileName)
	{
		m_Texture->CreateTextureFromFile(m_GA->m_pGraphicsAPIData, fileName);
	}

	void BETextureResource::Initialize()
	{
		Destroy();

		m_Texture = new BETexture();
		m_Texture->Initialize();
	}

	void BETextureResource::Destroy()
	{
		if (m_Texture != nullptr)
		{
			m_Texture->Destroy();
			delete m_Texture;
		}
	}
}