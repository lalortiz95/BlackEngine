#pragma once
#include "BEPrerequisitesCore.h"
#include "BEResource.h"

namespace BlackEngine
{
	class BETexture;
	class BEGraphicsAPI;

	class BE_CORE_EXPORT BETextureResource : public BEResource
	{
	public:
		BETextureResource();
		virtual ~BETextureResource();

		virtual void Load(const String& fileName) override;

		virtual void Initialize() override;
		virtual void Destroy() override;

		virtual RESOURCE_TYPE GetResourceType() override { return RT_TEXTURE; }

		///textura de la api.
		BETexture* m_Texture;
		BEGraphicsAPI* m_GA;
	};
}