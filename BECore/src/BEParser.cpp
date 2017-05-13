#include "BEParser.h"
#include <algorithm>

namespace BlackEngine
{
	typedef BlackEngine::String BEString;

	BEParser::BEParser()
	{
	}

	BEParser::BEParser(BEString Path)
	{
		m_FileName = Path;
	}


	BEParser::~BEParser()
	{
	}

	int BEParser::Parse(BlackEngine::String Cadena, char Separador, int offset)
	{
		///regresamos el primer separador que encontramos a partir de donde nosotros queremos.
		return Cadena.find(Separador, offset);
	}

	std::vector<String> BEParser::ParseToStr(String Cadena, String Separador, int offset)
	{
		std::vector<String> stringVector;
		SIZE_T iSeparation = 0;
		SIZE_T iOffset = offset;

		while (iOffset <= Cadena.length())
		{
			///guardamos el primer separador que encontramos a partir de donde nosotros queremos.
			iSeparation = Cadena.find(Separador, iOffset);
			if (iSeparation != String::npos)
			{
				///tomamos la parte de la cadena que queremos y la guardamos en una lista.
				stringVector.push_back(Cadena.substr(iOffset, iSeparation));
				///aumentamos el offset.
				iOffset += iSeparation;
			}

			//TODO: Insertar el ultimo tramo de el string a la lista

			else
			{
				break;
			}
		}
		return stringVector;
	}
}