#pragma once
#include "BEBuffer.h"
#include "BEVertex.h"

namespace BlackEngine
{
	struct GraphicsAPIData;
	class Vector3D;

	class BE_GRAPHICS_EXPORT BEVertexBuffer : public BEBuffer
	{
	public:
		BEVertexBuffer();
		~BEVertexBuffer();

		void Destroy();

		bool CreateBuffer(const GraphicsAPIData* pGraphicData);

		void AddVertex(VERTEX);

		//void Rotate(Vector4D angle);
		//void Scale(Vector4D scale);
		//void Translate(Vector4D position);

	private:
		Vector<VERTEX> m_Vertices;
	};
}