#pragma once
#include "Core.h"

#include "Window.h"
#include "PolyEngine/Core/LayerStack.h"
#include "PolyEngine/Events/Event.h"

#include "PolyEngine/Events/ApplicationEvent.h"
#include "PolyEngine/Core/Timestep.h"

#include "PolyEngine/ImGui/ImGuiLayer.h"


namespace PolyEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
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
	};

	Application* CreateApplication();

}
