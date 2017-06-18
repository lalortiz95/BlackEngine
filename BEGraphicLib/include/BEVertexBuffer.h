#pragma once
#include "BEBuffer.h"
#include "BEVertex.h"

///Engine's namespace.
namespace BlackEngine
{
	///Forward declarations
	struct GraphicsAPIData;

	class Vector3D;

	///Declaration of the vertex buffer class, inherits from buffer.
	class BE_GRAPHICS_EXPORT BEVertexBuffer : public BEBuffer
	{
	public:
		///Default constructor and destructor.
		BEVertexBuffer();
		~BEVertexBuffer();

		///This function releases memory and deletes the class' variables.
		void Destroy();

		///Creates a vertex buffer with the device.
		bool CreateBuffer(const GraphicsAPIData* pGraphicData);

		///Adds a vertex to the vertex vector.
		void AddVertex(VERTEX);

		//void Rotate(Vector4D angle);
		//void Scale(Vector4D scale);
		//void Translate(Vector4D position);

	private:
		///A vector where we store our vertices.  
		Vector<VERTEX> m_Vertices;
	};
}