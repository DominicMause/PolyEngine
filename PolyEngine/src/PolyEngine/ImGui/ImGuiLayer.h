#pragma once

#include "PolyEngine/Core/Layer.h"
#include "PolyEngine/Events/MouseEvent.h"
#include <PolyEngine/Events/KeyEvent.h>
#include <PolyEngine/Events/ApplicationEvent.h>

namespace PolyEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}