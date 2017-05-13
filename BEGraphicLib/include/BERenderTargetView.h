#pragma once
#include "BEPrerequisitesGraphics.h"

namespace BlackEngine
{
	struct RTVData;

	class BE_GRAPHICS_EXPORT BERenderTargetView
	{
	public:
		BERenderTargetView();
		~BERenderTargetView();

		void Initialize();
		void Destroy();

		RTVData* m_RTVData;
	};
}