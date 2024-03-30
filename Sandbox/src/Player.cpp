#include "Player.h"

Player::Player(const glm::vec2& position, const glm::vec2& size)
	: Entity(position, size), m_Camera(-(16.0f / 9.0f) * m_ZoomLevel, (16.0f / 9.0f)* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{
	for (int i = 0; i < 8; i++)
	{
		m_Coords.push_back(glm::vec2(-8.5f, 8.5f - i * 2.428571428571429f));
		m_Coords.push_back(glm::vec2( 8.5f, 8.5f - i * 2.428571428571429f));
	}
	m_IsAutoMode = true;
}

void Player::Update(Timestep time)
{
	glm::vec2 velocity = { 0,0 };

	if (Input::IsKeyPressed(POLY_KEY_A))
	{
		velocity.x -= 1;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_D))
	{
		velocity.x += 1;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_W))
	{
		velocity.y += 1;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_S))
	{
		velocity.y -= 1;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_ENTER))
	{
		m_IsAutoMode = true;
	}

	if (m_IsAutoMode && m_Coords.size())
	{
		velocity = glm::normalize(m_Coords.at(m_CurrentDestination) - m_Position);

		if (glm::distance(m_Position, m_Coords.at(m_CurrentDestination)) <= m_Radius)
		{
			if (m_CurrentDestination + 1 == m_Coords.size())
			{
				m_CurrentDestination = 0;
			}
			else
			{
				m_CurrentDestination++;
			}
		}
	}
	if (velocity.x != 0 || velocity.y != 0)
	{
		m_Position += glm::normalize(velocity) * glm::vec2(m_Speed * time);
	}

	m_Camera.SetPosition(glm::vec3(m_Position,0));
}

void Player::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(PE_BIND_EVENT_FN(Player::OnWindowResize));
	dispatcher.Dispatch<KeyPressedEvent>(PE_BIND_EVENT_FN(Player::OnKeyPressed));
}

bool Player::OnKeyPressed(KeyPressedEvent& e)
{
	if (!e.GetRepeatCount() && e.GetKeyCode() == POLY_KEY_E)
	{
		m_Coords.push_back(m_Position);
	}
	return false;
}

bool Player::OnWindowResize(WindowResizeEvent& e)
{
	float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}