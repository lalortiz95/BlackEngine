//#include "BEPrerequisitesCore.h"
#include "BEResourceManager.h"

#include "BETextureResource.h"
#include "BEModelResource.h"
#include <BEParser.h>

#include "BEModel.h"
#include <BETexture.h>
#include <BEFile.h>

#include <BEGraphicsAPI.h>

namespace BlackEngine
{
	BEResourceManager::BEResourceManager()
	{
		m_GA = nullptr;
	}

	BEResourceManager::~BEResourceManager()
	{
		Destroy();
	}

	void BEResourceManager::Initialize()
	{
		Destroy();

		m_GA = new BEGraphicsAPI();
	}

	void BEResourceManager::Destroy()
	{
		if (m_GA != nullptr)
		{
			delete m_GA;
		}
	}

	BEResource* BEResourceManager::LoadResourceFromFile(const String& fileName)
	{
		BEResource* pResourceToLoad = nullptr;
		BEParser parser;
		Vector<String> data;

		data = GetExtension(fileName);

		RESOURCE_TYPE resType = GetResourceTypeFromExtension(data.at(data.size() - 1));

		///Revisamos si el archivo ya habia sido cargado
		auto resourceIter = m_ResourcesMap.find(fileName);
		if (resourceIter != m_ResourcesMap.end())
		{///Quiere decir que ya existe en el mapa
			return resourceIter->second;
		}

		///Es un nuevo recurso
		switch (resType)
		{
		case RT_TEXTURE:
		{
			pResourceToLoad = new BETextureResource();
			BETextureResource* pTexture = dynamic_cast<BETextureResource*>(pResourceToLoad);
			pTexture->m_GA = m_GA;
			break;
		}
		case RT_MODEL:
		{
			pResourceToLoad = new BEModelResource();
			BEModelResource* pModel = dynamic_cast<BEModelResource*>(pResourceToLoad);
			pModel->m_GA = m_GA;
			break;
		}
		};

		if (nullptr != pResourceToLoad)
		{
			pResourceToLoad->Initialize();
			pResourceToLoad->Load(fileName);
			m_ResourcesMap[fileName] = pResourceToLoad;
			return pResourceToLoad;
		}

		return nullptr;
	}

	RESOURCE_TYPE BEResourceManager::GetResourceTypeFromExtension(const String& extension)
	{
		Map<String, RESOURCE_TYPE> extensionsType;
		BEUtilityString UtilString;
		String stringToCompare;

		extensionsType[".bmp"] = RT_TEXTURE;
		extensionsType[".png"] = RT_TEXTURE;
		extensionsType[".jpg"] = RT_TEXTURE;
		extensionsType[".fbx"] = RT_MODEL;
		extensionsType[".dae"] = RT_MODEL;
		extensionsType[".obj"] = RT_MODEL;
		extensionsType[".x"] = RT_MODEL;

		//TODO: arreglar esto.
		stringToCompare = UtilString.ToLowerCase(extension);

		for (auto iter : extensionsType)
		{
			if (iter.first.compare(extension.c_str()) == 0)
			{
				return iter.second;
			}
		}

		return RT_UNKNOWN;
	}

	Vector<String> BEResourceManager::GetExtension(const String & fileName)
	{
		BEParser parser;
		return parser.ParseToStr(fileName, ".", 0);
	}
	
	BEResourceManager& g_ResourceManager()
	{
		return BEResourceManager::Instance();
	}
}