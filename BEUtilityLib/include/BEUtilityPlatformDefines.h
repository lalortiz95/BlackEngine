#pragma once

/************************************************************************/
/* SISTEMA OPERATIVO                                                    */
/************************************************************************/

#define BE_PLATFORM_WIN32 1
#define BE_PLATFORM_LINUX 2
#define BE_PLATFORM_OSX 3
#define BE_PLATFORM_PS4 4

/************************************************************************/
/* TIPO DE COMPILADOR                                                   */
/************************************************************************/

#define BE_COMPILER_MSVC 1
#define BE_COMPILER_GNUC 2
#define BE_COMPILER_INTEL 3
#define BE_COMPILER_CLANG 4

/************************************************************************/
/* ARQUITECTURA                                                         */
/************************************************************************/

#define BE_ARCHITECTURE_x86_32 1
#define BE_ARCHITECTURE_x86_64 2
#define BE_ARCHITECTURE_ARM 2

/************************************************************************/
/* ENDIANS                                                              */
/************************************************************************/

///Little Endian
#define BE_ENDIAN_LITTLE 1 
///Big Endian
#define BE_ENDIAN_BIG 2 

#define BE_ENDIAN BE_ENDIAN_LITTLE

#define BE_EDITOR_BUILD 1

/************************************************************************/
/* Modo: DEBUG, RELEASE, PROFILE                                        */
/************************************************************************/

#define BE_DEBUG_MODE 1
#define BE_RELEASE_MODE 2
#define BE_PROFILE_MODE 3

/************************************************************************/
/*                                                                      */
/************************************************************************/



/************************************************************************/
/* TIPO DE COMPILADOR Y VERSIÓN                                         */
/************************************************************************/
#if defined(_MSC_VER)
	#define BE_COMPILER BE_COMPILER_MSVC
	#define BE_COMP_VER _MSC_VER
	#define BE_THREADLOCAL _declspec(thread)
#elif defined(__GNUC__)
	#define BE_COMPILER BE_COMPILER_GNUC
	#define BE_COMP_VER (((__GNUC__)*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
	#define BE_THREADLOCAL __thread
#elif defined(__INTEL_COMPILER)	
	#define BE_COMPILER BE_COMPILER_INTEL
	#define BE_COMP_VER __INTEL_COMPILER
#elif defined(__clang__)
	#define BE_COMPILER BE_COMPILER_CLANG
	#define BE_COMP_VER __clang_major__
	#define BE_THREADLOCAL __thread
#else
	#pragma error "no known compiler. "
#endif

/************************************************************************/
/* Ver si podemos usar __forceinline o si necesitamos __inline          */
/************************************************************************/
#if BE_COMPILER == BE_COMPILER_MSVC
	#if BE_COMP_VER >= 1200
		#define FORCEINLINE __forceinline
		#ifndef RESTRICT
			#define RESTRICT __restrict
		#endif
	#endif
#elif defined(__MINGW32__)
	#if !defined(FORCEINLINE)
		#define FORCEINLINE __inline
		#ifndef RESTRICT
			#define RESTRICT
		#endif
	#endif
#else
	#define FORCEINLINE __inline
	#ifndef RESTRICT
		#define RESTRICT __restrict
	#endif
#endif

/************************************************************************/
/* Encuentra la plataforma actual                                       */
/************************************************************************/
#if defined(__WIN32__) || defined(_WIN32) //Si es una plataforma de windows
	#define BE_PLATFORM BE_PLATFORM_WIN32
#elif defined(__APLE_CC__)
	#define BE_PLATFORM BE_PLATFORM_APPLE //Es una plataforma de apple
#elif defined(__ORBIS__)
	#define BE_PLATFORM BE_PLATFORM_PS4 //Es una plataforma de PSVITA
#else
	#define BE_PLATFORM BE_PLATFORM_LINUX //La tomaré como una plataforma de Linux
#endif

/************************************************************************/
/* Encuentra el tipo de arquitectura                                    */
/************************************************************************/
#if defined(__x86_64__) || defined(_M_X64)
	#define BE_ARCH_TYPE BE_ARCHITECTURE_X86_64 //Si será una compilación de x64
#else
	#define BE_ARCH_TYPE BE_ARCHITECTURE_X86_32 //Si será una compilación de x86
#endif

/************************************************************************/
/* Macros de memoria                                                    */
/************************************************************************/
#if BE_COMPILER == BE_COMPILER_MSVC
	#define MS_ALIGN(n) __declspec(align(n))
	#ifndef GCC_PACK
		#define GCC_PACK(n)
	#endif
	#ifndef GCC_ALIGN
		#define GCC_ALIGN(n)
	#endif
#elif ( BE_COMPILER == BE_COMPILER_GNUC && BE_PLATFORM == BE_PLATFORM_PS4)
	#define MS_ALIGN(n)
	#define GCC_PACK(n)
	#define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#else
	#define MS_ALIGN(n)
	#define GCC_PACK(n) __attribute__( (packed, aligned(n)) )
	#define GCC_ALIGN(n) __attribute__( (aligned(n)) )
#endif

/************************************************************************/
/* For throw override                                                   */
/************************************************************************/
#if BE_COMPILER == BE_COMPILER_MSVC
	#define _NOEXCEPT noexcept
#elif BE_COMPILER == BE_COMPILER_INTEL
	#define _NOEXCEPT noexcept
#elif BE_COMPILER == BE_COMPILER_GNUC
	#define _NOEXCEPT noexcept
#else
	#define _NOEXCEPT
#endif

/************************************************************************/
/* Propiedades específicas de windows                                   */
/************************************************************************/
//Definiciones para el manejo de la DLL
///ESTO ES MUY IMPORTANTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if BE_PLATFORM == BE_PLATFORM_WIN32
	#if defined( BE_STATIC_LIB)
		#define BE_UTILITY_EXPORT
	#else
		#if defined(BE_UTILITY_EXPORTS)
			#define BE_UTILITY_EXPORT __declspec(dllexport)
		#else
			#if defined (__WINGW32__)
				#define BE_UTILITY_EXPORT
			#else
				#define BE_UTILITY_EXPORT __declspec(dllimport)
			#endif
		#endif
	#endif

	#if defined(_DEBUG) || defined(DEBUG)
		#define BE_DEBUG_MODE 1
	#else 
		#define BE_DEBUG_MODE 0
	#endif

	#if BE_COMPILER == BE_COMPILER_INTEL
		#define BE_THREADLOCAL __declspec(thread)
	#endif
#endif

/************************************************************************/
/* Propiedades específicas de Linux/Apple                               */
/************************************************************************/
#if BE_PLATFORM == BE_PLATFORM_LINUX || BE_PLATFORM == BE_PLATFORM_OSX
	#if defined(BE_GCC_VISIBILITY)
		#define BE_UTILITY_EXPORT __attribute__ ((visibility("default")))
	#else
		#define BE_UTILITY_EXPORT
#endif

#define stricmp strcasecmp

///Si estamos en un build tipo DEBUG
#if defined(_DEBUG) || defined(DEBUG)
#define BE_DEBUG_MODE 1
#else
#define BE_DEBUG_MODE 0
#endif

#if BE_COMPILER == BE_COMPILER_INTEL
#define BE_THREADLOCAL __thread
#endif
#endif

/************************************************************************/
/* Propiedades específicas del PSVITA                                   */
/************************************************************************/
#if BE_PLATFORM == BE_PLATFORM_PS4
	#if defined(BE_STATIC_LIB)
		#define BE_UTILITY_EXPORT
	#else
		#if defined(BE_UTILIY_EXPORTS)
			#define BE_UTILITY_EXPORT __declspec(dllexport)
		#else
			#if defined (__WINGW32__)
				#define BE_UTILITY_EXPORT
			#else
				#define BE_UTILITY_EXPORT __declspec(dllimport)
			#endif
		#endif
	#endif

	#if defined(_DEBUG) || defined(DEBUG)
		#define BE_DEBUG_MODE 1
	#else 
		#define BE_DEBUG_MODE 0
	#endif
#endif


/************************************************************************/
/* Definiciones de macros de debug                                      */
/************************************************************************/
#if BE_DEBUG_MODE
	#define BE_DEBUG_ONLY(x) x
	#define BE_ASSERT(x) assert(x)
#else
	#define BE_DEBUG_ONLY(x)
	#define BE_ASSERT(x)
#endif

/************************************************************************/
/* TIPO DE COMPILADOR Y VERSIÓN                                         */
/************************************************************************/

#ifdef _WINDOWS
	#define BE_PLATFORM BE_PLATFORM_WIN32 //Estamos usando Windows
#endif // _WINDOWS

#ifdef __linux__
	#define BE_PLATFORM_LINUX //Estamos usando Linux
#endif

#ifdef _PSVITA
	#define BE_PLATFORM BE_PLATFORM_PSVITA //Estamos usando PSVITA
#endif