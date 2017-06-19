#pragma once
#include "BEPrerequisitesGraphics.h"

///The engine's namespace.
namespace BlackEngine
{
	///Forward declarations.
	struct GraphicsAPIData;
	struct RTVData;

	class BETexture;
	class Vector4D;
	
	///Declaration of Render Target View class.
	class BE_GRAPHICS_EXPORT BERenderTargetView
	{
	public:
		///Default constructor and destructor.
		BERenderTargetView();
		~BERenderTargetView();

		///This functions give and release memory from the class' variables.
		void Initialize();
		void Destroy();

		///Cleans the render target view.
		void Clear(Vector4D cleanUpColor, const GraphicsAPIData * pGraphicData);
		///creates the RTV
		bool Create(BETexture* Texture, const GraphicsAPIData * pGraphicData);
		
		///This variable stores the RTV data.
		RTVData* m_RTVData;
	};
}