#pragma once
#include "BEPrerequisitesGraphics.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct RasterizerStateData;
	struct GraphicsAPIData;

	///Definition of the Rasterizer state class.
	class BE_GRAPHICS_EXPORT BERasterizerState
	{
	public:
		///Default constructor and destruuctor.
		BERasterizerState();
		~BERasterizerState();

		///This functions give and release memory from the class' variables.
		bool Initialize();
		void Destroy();

		///Creates a rasterizer state.
		bool Create(const GraphicsAPIData * gData);
		//TODO: tener variables miembras que llenen la información del descriptor.
		///variable where we store the Rasterizer state data.
		RasterizerStateData* m_RSData;
	};
}