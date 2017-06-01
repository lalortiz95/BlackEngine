#pragma once
#include "BEPrerequisitesEngine.h"

namespace BlackEngine
{
	enum RESOURCE_TYPE
	{
		RT_UNKNOWN,
		RT_TEXTURE,
		RT_MODEL,
		RT_MATERIAL,
		RT_NUMMAX
	};

	class BE_ENGINE_EXPORT BEResource
	{
	public:
		virtual ~BEResource();

		virtual void Initialize() = 0;
		virtual void Destroy() = 0;
		virtual void Load(const String& fileName) = 0;
		virtual RESOURCE_TYPE GetResourceType() = 0;

		///ID del recurso que tiene.
		String m_ResourceHandler;
	};
}