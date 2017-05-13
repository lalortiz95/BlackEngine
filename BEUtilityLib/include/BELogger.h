#pragma once
#include "BEStdHeaders.h"
#include "BEPrerequisitesUtility.h"

namespace BlackEngine
{
	class BE_UTILITY_EXPORT Logger
	{
	public:
		enum eMessage
		{
			BE_GENERAL = 0,
			BE_WARNING = 1,
			BE_ERROR = 2,
			BE_FATALERROR = 3
		};

		String m_FileName;
		void StartLogger(char* szFileName);

		void SendMessage(int type, String Msg, int Line);

	};
}