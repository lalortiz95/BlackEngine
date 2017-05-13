#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct BufferData;
	struct GraphicsAPIData;

	class BE_GRAPHICS_EXPORT BEBuffer
	{
	public:
		BEBuffer();
		virtual ~BEBuffer();

		void Initialize();
		void Destroy();

		virtual bool CreateBuffer(const GraphicsAPIData* pGraphicData) = 0;

		BufferData* m_BufferData;
		///vertex buffer
		///index buffer
		///constant buffer
	};
}