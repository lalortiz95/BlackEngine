#include "BEUtilityPCH.h"
#include "BEFile.h"

namespace BlackEngine
{
	BEFile::BEFile()
	{
	}


	BEFile::~BEFile()
	{
	}

	int32 BEFile::Read(char* dst, SIZE_T ByteCount)
	{
		m_Stream.read(dst, ByteCount);
		m_Stream.seekg(ByteCount);
		return 0;
	}

	int32 BEFile::Write(char* /*src*/, SIZE_T /*ByteCount*/)
	{
		return 0;
	}

	void BEFile::Open(const char* FileName)
	{
		m_Stream.open(FileName, std::ios::in | std::ios::out | std::ios::ate);
		m_Size = (SIZE_T)m_Stream.tellg();
		m_Stream.seekg(0, std::ios::beg);
	}

	void BEFile::Close()
	{
		m_Stream.close();
	}
}
