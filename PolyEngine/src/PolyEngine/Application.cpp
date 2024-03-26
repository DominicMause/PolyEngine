#include "pepch.h"
#include "Application.h"

#include "PolyEngine/Events/ApplicationEvent.h"
#include "PolyEngine/Log.h"

#include "GLFW/glfw3.h"

namespace PolyEngine {

	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}