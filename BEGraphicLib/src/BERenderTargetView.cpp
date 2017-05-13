#include "BERenderTargetView.h"
#include "DirectXData.h"

namespace BlackEngine
{

	BERenderTargetView::BERenderTargetView()
	{
		m_RTVData = nullptr;
	}

	BERenderTargetView::~BERenderTargetView()
	{
	}

	void BERenderTargetView::Initialize()
	{
		m_RTVData = new RTVData();
	}

	void BERenderTargetView::Destroy()
	{
		delete(this);
	}

}
