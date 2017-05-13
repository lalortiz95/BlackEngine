#pragma once

#include <BEPrerequisitesUtility.h>
#include <BEUtilityString.h>

#if defined(BE_ENGINE_EXPORTS)
#	define BE_ENGINE_EXPORT __declspec(dllexport)
#elif (BE_ENGINE_STATIC)
#	define BE_ENGINE_EXPORT 
#else
#	define BE_ENGINE_EXPORT __declspec(dllimport)
#endif