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

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x,...) {if(!(x)) { PE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CORE_ASSERT(x, ...) { if(!(x)) { PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif // PE_ENABLE_ASSERTS


#define BIT(x) (1 << x)