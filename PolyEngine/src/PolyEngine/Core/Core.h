#pragma once

#include <memory>

#ifdef PE_PLATFORM_WINDOWS

#else
	#error PolyEngine only supports Windows!
#endif

#ifdef PE_DEBUG
	#define PE_ENABLE_ASSERTS
#endif

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x,...) {if(!(x)) { PE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CORE_ASSERT(x, ...) { if(!(x)) { PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif // PE_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define PE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace PolyEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}