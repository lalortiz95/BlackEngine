#pragma once
#include "BEBuffer.h"

namespace BlackEngine
{
	class BE_GRAPHICS_EXPORT BEIndexBuffer : public BEBuffer
	{
	public:
		BEIndexBuffer();
		~BEIndexBuffer();

		void Initialize();
		void Destroy();

		bool CreateBuffer(const GraphicsAPIData* pGraphicData);
		uint32 GetIndicesSize() { return (uint32)m_Indices.size(); }

		void AddIndex(uint32);
	private:
		Vector<uint32> m_Indices;
	};
}

