#pragma once
#include "BEPrerequisitesEngine.h"
#include "BEResource.h"
#include "BEMaterial.h"

namespace BlackEngine
{
	class BE_ENGINE_EXPORT BEMaterialResource : public BEResource
	{
	public:
		BEMaterialResource();
		virtual ~BEMaterialResource();

		virtual void Load(const String& fileName) override;

		virtual void Initialize() override;
		virtual void Destroy() override;

		virtual RESOURCE_TYPE GetResourceType() override { return RT_MATERIAL; }

		BEMaterial* m_Material;
	};
}
