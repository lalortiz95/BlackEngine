#pragma once
#include <BEPrerequisitesUtility.h>

#if defined(BE_RENDERMACHINE_EXPORTS)
#	define BE_RENDERMACHINE_EXPORT __declspec(dllexport)
#elif (BE_RENDERMACHINE_STATIC)
#	define BE_RENDERMACHINE_EXPORT 
#else
#	define BE_RENDERMACHINE_EXPORT __declspec(dllimport)
#endif