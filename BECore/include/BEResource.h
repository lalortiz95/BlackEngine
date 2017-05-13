#pragma once
#include "BEPrerequisitesCore.h"

namespace BlackEngine
{
	enum RESOURCE_TYPE
	{
		RT_UNKNOWN,
		RT_TEXTURE,
		RT_MODEL,
		RT_NUMMAX
	};

	class BE_CORE_EXPORT BEResource
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