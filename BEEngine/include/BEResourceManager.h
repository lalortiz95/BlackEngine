#pragma once
#include "BEResource.h"

namespace BlackEngine
{
	class BEGraphicsAPI;

	class BE_ENGINE_EXPORT BEResourceManager
	{
	public:
		BEResourceManager();
		~BEResourceManager();
		
		void Initialize();
		void Destroy();
		BEResource* LoadResourceFromFile(const String& fileName);
		void UnloadResource();
		RESOURCE_TYPE GetResourceTypeFromExtension(const String& extension);
		Vector<String> GetExtension(const String& fileName);

		///mapa que tiene al recurso y un identificador de éste.
		Map<String, BEResource*> m_ResourcesMap;
		BEGraphicsAPI* m_GA;

	private:
		BEResource* m_resourceToLoad;
	};
}