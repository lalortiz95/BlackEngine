#pragma once
#include "BEPrerequisitesUtility.h"
#include <wchar.h>

namespace BlackEngine
{
	template <typename T>
	using BasicString = std::basic_string<T, std::char_traits<T>, /*StdAlloc<T>*/ std::allocator<T> >;

	///basic string stream that uses black engine memory allocators.
	template <typename T>
	using BasicStringStream = std::basic_stringstream<T, std::char_traits<T>, /*StdAlloc<T>*/ std::allocator<T>>;

	///wide string used primarily for handling unicode text
	typedef BasicString<UNICHAR> WString;

	///narrow string used primarily for handling ASCII text
	typedef BasicString<ANSICHAR> String;

	///wide string stream used for primarily for constructing strings consisting of unicode text
	typedef BasicStringStream<UNICHAR> WStringStream;

	///wide string stream used for primarily for constructing strings consisting of ASCIItext
	typedef BasicStringStream<ANSICHAR> StringStream;

	class BE_UTILITY_EXPORT BEUtilityString
	{
	public:
		BEUtilityString();
		~BEUtilityString();

		///trim va a cortar el caracter o la cadena que le indiquemos, en la orilla de la cadena original.
		String Trim(const String& Cadena, const String& objToTrim);
		///split, nos regresa un vector de strings, cada uno lo separa el separador que se haya indicado
		///empieza a partir del offset que se le da.
		Vector<String> Split(const String& Cadena, const String& Separador, int32 offset);
		String ToLowerCase(const String& Cadena);
		String ToUpperCase(const String& Cadena);
		bool StartWith(const String&, const String&, bool IsUpperCase);
		bool StartWith(const WString&, const WString& Pattern, bool IsUpperCase);

		WString StringToWide(const String& str);
		String WideToString(const WString& wstr);

		template <class T>
		bool Compare(const String&);

		template <class T, class... Args>
		static BasicString<T> Format();
	};

	template<class T>
	inline bool BEUtilityString::Compare(const String& str)
	{
		//TO-DO:
		//str.compare();
		return false;
	}
}

