#include "BEUtilityString.h"

namespace BlackEngine
{
	BEUtilityString::BEUtilityString()
	{
	}


	BEUtilityString::~BEUtilityString()
	{
	}

	String BEUtilityString::Trim(const String& Cadena, const String& objToTrim)
	{
		String stringWeWant, obj;
		String::iterator it;

		stringWeWant = Cadena;
		obj = objToTrim;

		///reviso que esté el objeto al inicio de la cadena, si lo hay lo borro.
		while (stringWeWant.find(obj) == 0)
		{
			it = stringWeWant.begin();
			stringWeWant.erase(it);
		}

		///reviso que esté el objeto al final de la cadena, so lo está, lo borro.
		while (stringWeWant.find(objToTrim) == stringWeWant.size())
		{
			it = stringWeWant.end();
			stringWeWant.erase(it);
		}

		return stringWeWant;
	}

	Vector<String> BEUtilityString::Split(const String& Cadena, const String& Separador, int32 offset)
	{
		Vector<String> stringVector;
		size_t iSeparation = 0;
		int iOffset = offset;

		while (iOffset <= (int32)Cadena.length())
		{
			///guardamos el primer separador que encontramos a partir de donde nosotros queremos.
			iSeparation = Cadena.find(Separador.c_str(), iOffset);
			if (iSeparation != std::string::npos)
			{
				///tomamos la parte de la cadena que queremos y la guardamos en una lista.
				stringVector.push_back(Cadena.substr(iOffset, iSeparation));
				///aumentamos el offset.
				iOffset += iSeparation;
			}
		}
		return stringVector;
	}

	String BEUtilityString::ToLowerCase(const String& Cadena)
	{
		String strLower = Cadena;
		std::transform(strLower.begin(), strLower.end(), strLower.begin(), tolower);
		//TODO:cuando se sale la funcion el valor de strLower se vuelve "", creo que ahí
		//radica el problema.
		return strLower;
	}

	String BEUtilityString::ToUpperCase(const String& Cadena)
	{
		String strUpper = Cadena;
		std::transform(strUpper.begin(), strUpper.end(), strUpper.begin(), toupper);

		return strUpper;
	}

	bool BEUtilityString::StartWith(const String& txt, const String& txtToFind, bool /*IsUpperCase*/)
	{
		///revisa que se haya encontrado la cadena que se deseaba en el inicio del string.
		if (txt.find(txtToFind) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool BEUtilityString::StartWith(const WString& txt, const WString& txtToFind, bool /*IsUpperCase*/)
	{
		if (txt.find(txtToFind) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	WString BEUtilityString::StringToWide(const String & str)
	{
		WString miwString;
		miwString.insert(miwString.begin(), str.begin(), str.end());
		return miwString;
	}

	String BEUtilityString::WideToString(const WString & wstr)
	{
		String MyString;
		MyString.insert(MyString.begin(), wstr.begin(), wstr.end());
		return MyString;
	}
}