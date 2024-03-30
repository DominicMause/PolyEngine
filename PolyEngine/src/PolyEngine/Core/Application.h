#pragma once
#include "Core.h"

#include "Window.h"
#include "PolyEngine/Core/LayerStack.h"
#include "PolyEngine/Events/Event.h"

#include "PolyEngine/Events/ApplicationEvent.h"
#include "PolyEngine/Core/Timestep.h"

#include "PolyEngine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace PolyEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();

}
