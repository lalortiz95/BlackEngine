#include "BEDepthStencilView.h"
#include <Vector3D.h>
#include "DirectXData.h"

namespace BlackEngine
{
	struct DSVData;
	BEDepthStencilView::BEDepthStencilView()
	{
		m_DSVData = nullptr;
		Initialize();
	}

	BEDepthStencilView::~BEDepthStencilView()
	{
		Destroy();
	}

	void BEDepthStencilView::Initialize()
	{
		m_DSVData = new DSVData();
	}

	void BEDepthStencilView::Destroy()
	{
		if (m_DSVData != nullptr)
		{
			m_DSVData->Destroy();
			delete m_DSVData;
			m_DSVData = nullptr;
		}
	}
}