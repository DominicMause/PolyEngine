#pragma once
#include "Core.h"

#include "Window.h"
#include "PolyEngine/LayerStack.h"
#include "Events/Event.h"

#include "PolyEngine/Events/ApplicationEvent.h"

#include "PolyEngine/ImGui/ImGuiLayer.h"

#include "PolyEngine/Renderer/Shader.h"

namespace PolyEngine {

	class POLY_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}
