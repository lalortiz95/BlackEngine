#include "BEDepthStencilView.h"
#include <Vector3D.h>
#include "DirectXData.h"

namespace BlackEngine
{
	struct DSVData;
	BEDepthStencilView::BEDepthStencilView()
	{
		m_DSVData = nullptr;
	}

	BEDepthStencilView::~BEDepthStencilView()
	{
	}

	void BEDepthStencilView::Initialize()
	{
		m_DSVData = new DSVData();
	}

	void BEDepthStencilView::Destroy()
	{
		delete(this);
	}
}