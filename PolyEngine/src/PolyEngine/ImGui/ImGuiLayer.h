#pragma once

#include "PolyEngine/Core/Layer.h"
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
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}