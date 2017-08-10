#pragma once
#include "BEBuffer.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct GraphicsAPIData;

	///Constant buffer class declaration. inherits from BEBuffer.
	class BE_GRAPHICS_EXPORT BEConstantBuffer : public BEBuffer
	{
	public:
		///Default constructor and destructor.
		BEConstantBuffer();
		~BEConstantBuffer();

		///This function releases memory, and deletes the member objects.
		void Destroy();

		///creates the buffer.
		bool CreateBuffer();
	};
}