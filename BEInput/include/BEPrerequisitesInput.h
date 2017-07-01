#pragma once

#include <BEPrerequisitesUtility.h>

#if defined(BE_INPUT_EXPORTS)
#	define BE_INPUT_EXPORT __declspec(dllexport)
#elif (BE_INPUT_STATIC)
#	define BE_INPUT_EXPORT 
#else
#	define BE_INPUT_EXPORT __declspec(dllimport)
#endif