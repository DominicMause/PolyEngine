#include "pepch.h"
#include "Input.h"

#ifdef PE_PLATFORM_WINDOWS
#include "PolyEngine/Platform/Windows/WindowsInput.h"
#endif // PE_PLATFORM_WINDOWS

namespace PolyEngine
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef PE_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			HZ_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif // PE_PLATFORM_WINDOWS
	}
}
