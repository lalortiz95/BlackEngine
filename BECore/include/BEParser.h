#pragma once

#include "BEPrerequisitesCore.h"


namespace BlackEngine
{
	typedef BlackEngine::String BEString;

	class BE_CORE_EXPORT BEParser
	{
	public:
		BEParser();
		BEParser(BEString Path);
		~BEParser();

		int Parse(BlackEngine::String Cadena, char Separador, int offset);
		std::vector<BlackEngine::String> ParseToStr(BlackEngine::String Cadena, BlackEngine::String Separador, int offset);

		bool m_bIsString;
		BlackEngine::String m_FileName;
		bool m_bIsAbsolute;
		BlackEngine::String m_Extension;
	};
}