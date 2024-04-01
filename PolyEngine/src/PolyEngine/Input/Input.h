#pragma once

#include "PolyEngine/Core/Core.h"
#include "PolyEngine/Input/KeyCodes.h"
#include "PolyEngine/Input/MouseCodes.h"

namespace PolyEngine
{

	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(KeyCode keycode)
		{
			return s_Instance->IsKeyPressedImpl(keycode);
		}

		static bool IsMouseButtonPressed(MouseCode button)
		{
			return s_Instance->IsMouseButtonPressedImpl(button);
		}

		static std::pair<float,float> GetMousePosition()
		{
			return s_Instance->GetMousePositionImpl();
		}

		static float GetMouseX()
		{
			return s_Instance->GetMouseXImpl();
		}

		static float GetMouseY()
		{
			return s_Instance->GetMouseYImpl();
		}

		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	private:
		static Scope<Input> s_Instance;
	};

}