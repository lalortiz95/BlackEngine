#pragma once
#include "BEPrerequisitesEngine.h"
#include "BEResource.h"

namespace BlackEngine
{
	class BEModel;

	class BE_ENGINE_EXPORT BEModelResource : public BEResource
	{
	public:
		BEModelResource();
		virtual ~BEModelResource();

		virtual void Load(const String& fileName) override;

		virtual void Initialize() override;
		virtual void Destroy() override;

		virtual RESOURCE_TYPE GetResourceType() override { return RT_MODEL; }

		BEModel* m_Model;
		///vaiable de la api gr�fica para la creaci�n de los buffers.
	};
}

