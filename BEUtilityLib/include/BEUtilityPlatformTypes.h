#pragma once
#include "BEUtilityPlatformDefines.h"

namespace BlackEngine
{
	/************************************************************************/
	/* Tipos basicos sin signo                                                                     */
	/************************************************************************/
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;

#if BE_COMPILER == BE_COMPILER_MSVC
	typedef unsigned __int64 uint64;
#else
	typedef unsigned long uint64;
#endif

	/************************************************************************/
	/* Tipos básicos con signo                                              */
	/************************************************************************/
	typedef signed char int8;
	typedef signed short int16;
	typedef signed int int32;
#if BE_COMPILER == BE_COMPILER_MSVC
	typedef signed __int64 int64;
#else
	typedef signed long int64;
#endif

	MS_ALIGN(16) class QWord
	{
	public:
		uint64 m_lower;
		int64 m_upper;
		
		///return: the lower 64 bits of the value.
		operator int64() const
		{
			return m_lower;
		}

		///default constructor
		QWord() : m_lower(0), m_upper(0)
		{

		}

		QWord(bool from) : m_lower(from), m_upper(0)
		{

		}

		QWord(uint8 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(int8 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(uint16 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(int16 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(uint32 from) : m_lower(from), m_upper(0)
		{

		}
	
		QWord(int32 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(uint64 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(int64 from) : m_lower(from), m_upper(0)
		{

		}

		QWord(float from) : m_lower((uint64)from), m_upper(0)
		{

		}

		QWord(double from) : m_lower((uint64)from), m_upper(0)
		{

		}
	}GCC_ALIGN(16);

	typedef QWord int128; //entero de 128 bits con signo
	typedef QWord uint128; //entero de 128 bits sin signo


	/************************************************************************/
	/* Tipos de char                                                        */
	/************************************************************************/
#if BE_COMPILER == BE_COMPILER_MSVC || BE_PLATFORM == BE_PLATFORM_PS4
	typedef wchar_t			WCHAR;
#else
	typedef unsigned short	WCHAR;
#endif
	typedef char			ANSICHAR; //Tipo ANSI de caracter
	typedef WCHAR			UNICHAR; //Tipo UNICODE de caracter

	/************************************************************************/
	/* Tipos NULL de datos                                                  */
	/************************************************************************/
	typedef int32 TYPE_OF_NULL;

	/************************************************************************/
	/* SIZE_T es una arquitectura dependiente del tipo de dato              */
	/************************************************************************/
#if((BE_ARCH_TYPE == BE_ARCHITECTURE_x86_64) && (BE_COMPILER == BE_COMPILER_MSVC))
	typedef unsigned __int64	SIZE_T;
#else
	typedef unsigned long		SIZE_T;
#endif
}