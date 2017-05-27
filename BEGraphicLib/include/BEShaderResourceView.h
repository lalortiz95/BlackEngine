#pragma once
#include "BEPrerequisitesGraphics.h"
#include "BETexture.h"

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

		bool Create(const GraphicsAPIData* GData,/*, const String& Addr*/BETexture data);

		ShaderResourceViewData* m_SRVData;
	};
}