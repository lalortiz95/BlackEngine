#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct GraphicsAPIData;
	struct ShaderResourceViewData;

	class BE_GRAPHICS_EXPORT BEShaderResourceView
	{
	public:
		BEShaderResourceView();
		~BEShaderResourceView();

		bool Initialize();
		void Destroy();

		bool Create(const GraphicsAPIData* GData, const String* Addr);

		ShaderResourceViewData* m_SRVData;
	};
}