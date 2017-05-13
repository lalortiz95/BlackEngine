#include "BEBuffer.h"
#include "DirectXData.h"

namespace BlackEngine
{

	BEBuffer::BEBuffer()
	{
		m_BufferData = nullptr;
	}


	BEBuffer::~BEBuffer()
	{
		Destroy();
	}

	void BEBuffer::Initialize()
	{
		m_BufferData = new BufferData();
	}

	void BEBuffer::Destroy()
	{
		if (m_BufferData != nullptr)
		{
			m_BufferData->Destroy();
			m_BufferData = nullptr;
		}
	}

}