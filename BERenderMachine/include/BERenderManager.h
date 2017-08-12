#pragma once
#include "BEPrerequisitesRenderMachine.h"
#include <BERenderTargetView.h>
#include <BEModel.h>

namespace BlackEngine
{
	class BE_RENDERMACHINE_EXPORT BERenderManager
	{
	public:
		BERenderManager();
		~BERenderManager();

		void Initialize();
		void Destroy();

		void Run();

		BERenderTargetView* m_RenderTargets;
		BEModel* m_Models;
	};
}