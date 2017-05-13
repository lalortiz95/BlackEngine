#pragma once

#include <BEPrerequisitesUtility.h>
#include <BEUtilityString.h>

#if defined(BE_CORE_EXPORTS)
#	define BE_CORE_EXPORT __declspec(dllexport)
#elif (BE_CORE_STATIC)
#	define BE_CORE_EXPORT 
#else
#	define BE_CORE_EXPORT __declspec(dllimport)
#endif