#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct DSVData;
	class BE_GRAPHICS_EXPORT BEDepthStencilView
	{
	public:
		BEDepthStencilView();
		~BEDepthStencilView();

		void Initialize();
		void Destroy();

		DSVData* m_DSVData;
	};
}