#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct InputLayoutData;
	struct GraphicsAPIData;

	class BEVertexShader;

	class BE_GRAPHICS_EXPORT BEInputLayout
	{
	public:
		BEInputLayout();
		~BEInputLayout();

		void Initialize();
		void Destroy();
		bool CreateInputLayout(GraphicsAPIData&, BEVertexShader*);

		InputLayoutData* m_ILData;
	};
}