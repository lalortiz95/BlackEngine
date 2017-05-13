#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct GraphicsAPIData;
	struct SamplerData;

	class BE_GRAPHICS_EXPORT BESampler
	{
	public:
		BESampler();
		~BESampler();

		void Initialize();
		void Destroy();

		void Create(const GraphicsAPIData* GData);

		SamplerData* m_SD;
	};
}