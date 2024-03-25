#pragma once

#ifdef PE_PLATFORM_WINDOWS
	#ifdef PE_BUILD_DLL
		#define POLY_API __declspec(dllexport)
	#else
		#define POLY_API __declspec(dllimport)
	#endif
#else
	#error PolyEngine only supports Windows!
#endif
