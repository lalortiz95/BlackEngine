#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct RasterizerStateData;
	struct GraphicsAPIData;

	class BE_GRAPHICS_EXPORT BERasterizerState
	{
	public:
		BERasterizerState();
		~BERasterizerState();

		bool Initialize();
		void Destroy();
		bool Create(const GraphicsAPIData * gData);
		//TODO: tener variables miembras que llenen la información del descriptor.
		
		RasterizerStateData* m_RSData;
	};
}