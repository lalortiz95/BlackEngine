#pragma once

#include <BEPrerequisitesUtility.h>

#if defined(BE_GRAPHICS_EXPORTS)
#	define BE_GRAPHICS_EXPORT __declspec(dllexport)
#elif defined(BE_GRAPHICS_STATIC)
#	define BE_GRAPHICS_EXPORT 
#else
#	define BE_GRAPHICS_EXPORT __declspec(dllimport)
#endif