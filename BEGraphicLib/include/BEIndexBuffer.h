#pragma once
#include "BEBuffer.h"

///The engine's namespace
namespace BlackEngine
{
	///Declaration of the index buffer class, that inherits from BEBuffer.
	class BE_GRAPHICS_EXPORT BEIndexBuffer : public BEBuffer
	{
	public:
		///Default constructor and destructor.
		BEIndexBuffer();
		~BEIndexBuffer();

		///This function initializes the class' variables.
		void Initialize();
		///Releases memory, and deletes the class' variables.
		void Destroy();
		///Creates a index Buffer.
		bool CreateBuffer();
		///Function that returns how many indices are in the class.
		uint32 GetIndicesSize() { return (uint32)m_Indices.size(); }
		///Adds an index to the Index vector.
		void AddIndex(uint32);
	
	private:
		///A vector to store al of our indices.
		Vector<uint32> m_Indices;
	};
}

