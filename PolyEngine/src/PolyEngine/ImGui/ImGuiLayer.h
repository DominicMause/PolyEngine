#pragma once

#include "PolyEngine/Layer.h"
#include "PolyEngine/Events/MouseEvent.h"
#include <PolyEngine/Events/KeyEvent.h>
#include <PolyEngine/Events/ApplicationEvent.h>

namespace PolyEngine
{
	class POLY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);

	private:
		float m_Time = 0.0f;
	};
}