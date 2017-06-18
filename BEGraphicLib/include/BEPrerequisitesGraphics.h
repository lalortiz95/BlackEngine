#pragma once
#include <BEPrerequisitesUtility.h>

///Here we define a Graphics export constant, that when specified in a class
///That class will be exported to de library.
#if defined(BE_GRAPHICS_EXPORTS)
#	define BE_GRAPHICS_EXPORT __declspec(dllexport)
#elif defined(BE_GRAPHICS_STATIC)
#	define BE_GRAPHICS_EXPORT 
#else
#	define BE_GRAPHICS_EXPORT __declspec(dllimport)
#endif