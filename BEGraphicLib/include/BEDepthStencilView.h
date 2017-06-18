#pragma once
#include "BEPrerequisitesGraphics.h"

///Engine's namespace
namespace BlackEngine
{
	///Forward declarations
	struct DSVData;

	///Declaration of Depth Stencil View
	class BE_GRAPHICS_EXPORT BEDepthStencilView
	{
	public:
		///Default constructor and destructor.
		BEDepthStencilView();
		~BEDepthStencilView();

		///This function initializes and allocates memory to the class' variables.
		void Initialize();
		///This function releases memory and deletes the objects.
		void Destroy();

		///depth stencil view variable that points to the api type.
		DSVData* m_DSVData;
	};
}