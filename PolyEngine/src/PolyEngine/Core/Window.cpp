#include "pepch.h"
#include "Window.h"

#ifdef PE_PLATFORM_WINDOWS
	#include "PolyEngine/Platform/Windows/WindowsWindow.h"
#endif // PE_PLATFORM_WINDOWS

namespace PolyEngine
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef PE_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			PE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}
