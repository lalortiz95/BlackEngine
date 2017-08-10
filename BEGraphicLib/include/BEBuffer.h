#pragma once
#include "BEPrerequisitesGraphics.h"

///The engine's namespace.
namespace BlackEngine
{
	//The namespace for our enum, the enum E stores the 
	//flags for the type of buffer.
	//namespace BUFFER_CREATION
	//{
	//	enum E
	//	{
	//		kDefault = 0x00,
	//		kConstantBuffer = 0x01,
	//		kIndexBuffer = 0x02,
	//		kVertexBuffer = 0x03
	//	};
	//}

	///Forward declarations.
	struct BufferData;
	struct GraphicsAPIData;

	///Base class BEBuffer.
	class BE_GRAPHICS_EXPORT BEBuffer
	{
	public:
		///Default constructor and destructor.
		BEBuffer();
		virtual ~BEBuffer();

		///This function allocates memory,and initializes it's variables.
		void Initialize();
		///Releases memory of the variables, and deletes them.
		void Destroy();
		///The device creates a buffer.
		virtual bool CreateBuffer()=0;
		///variable where the buffer data is stored.
		BufferData* m_BufferData;
	};
}