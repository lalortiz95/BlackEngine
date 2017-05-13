#include <BEParser.h>

int main()
{
	BlackEngine::BEParser ParserUT;

	std::vector<BlackEngine::String> ParsedStr;
	BlackEngine::int32 separator;

	separator = ParserUT.Parse("hola mundo, test del, parse", ',', 0);
	std::cout << "separador encontrado en el lugar " << separator << " de la cadena." << std::endl;
	ParsedStr = ParserUT.ParseToStr("hola mundo, test del, parse", ",", 0);

	for (size_t i = 0; i < ParsedStr.size(); i++)
	{
		std::cout << ParsedStr[i].c_str() << std::endl;
	}

	return 0;
}