#pragma once
#include "BEPrerequisitesGraphics.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct InputLayoutData;
	struct GraphicsAPIData;

	class BEVertexShader;

	///Declaration of BEInputLayout class, we set it so that it gets exported to the library.
	class BE_GRAPHICS_EXPORT BEInputLayout
	{
	public:
		///Default Constructor and destructor.
		BEInputLayout();
		~BEInputLayout();

		///This functions give and release memory from the class' variables.
		void Initialize();
		void Destroy();
		///Creates the input layout.
		bool CreateInputLayout(GraphicsAPIData&, BEVertexShader*);


		///variable where we store de Input Layout data.
		InputLayoutData* m_ILData;
	};
}