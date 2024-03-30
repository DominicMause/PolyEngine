#include "pepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace PolyEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		PE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PE_CORE_ASSERT(status, "Failed to initialize Glad");

		PE_CORE_INFO("OpenGL Renderer:");
		PE_CORE_INFO("       Vendor:   {0}", (const char*)glGetString(GL_VENDOR));
		PE_CORE_INFO("       Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PE_CORE_INFO("       Version:  {0}", (const char*)glGetString(GL_VERSION));

		#ifdef PE_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			PE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "PolyEngine requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		PE_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}