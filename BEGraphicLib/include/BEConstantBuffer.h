#pragma once
#include "BEBuffer.h"

namespace BlackEngine
{
	struct GraphicsAPIData;

	class BE_GRAPHICS_EXPORT BEConstantBuffer : public BEBuffer
	{
	public:
		BEConstantBuffer();
		~BEConstantBuffer();

		void Destroy();

		bool CreateBuffer(const GraphicsAPIData * pGraphicData);
	};
}