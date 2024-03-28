#include "pepch.h"
#include "OrthographicCameraController.h"
#include "PolyEngine/Input/Input.h"
#include "PolyEngine/Input/KeyCodes.h"

namespace PolyEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotaion(rotation), m_AspectRatio(aspectRatio)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(POLY_KEY_W))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (m_Rotaion)
		{
			if (Input::IsKeyPressed(POLY_KEY_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			if (Input::IsKeyPressed(POLY_KEY_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(PE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		m_CameraTranslationSpeed = m_ZoomLevel;
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}