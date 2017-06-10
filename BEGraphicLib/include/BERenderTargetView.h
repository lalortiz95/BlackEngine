#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct GraphicsAPIData;
	struct RTVData;
	class BETexture;
	class Vector4D;
	
	class BE_GRAPHICS_EXPORT BERenderTargetView
	{
	public:
		BERenderTargetView();
		~BERenderTargetView();

		void Initialize();
		void Destroy();

		///limpia el render target view.
		void Clear(Vector4D cleanUpColor, const GraphicsAPIData * pGraphicData);
		///crea el RTV
		bool Create(BETexture* Texture, const GraphicsAPIData * pGraphicData);

		RTVData* m_RTVData;
	};
}