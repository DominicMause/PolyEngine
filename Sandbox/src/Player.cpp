#include "Player.h"

Player::Player(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	: Entity(position, size, texture)
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
		velocity.x -= m_Speed * time;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_D))
	{
		velocity.x += m_Speed * time;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_W))
	{
		velocity.y += m_Speed * time;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_S))
	{
		velocity.y -= m_Speed * time;
		m_IsAutoMode = false;
	}
	if (Input::IsKeyPressed(POLY_KEY_ENTER))
	{
		m_IsAutoMode = true;
	}

	if (m_IsAutoMode && m_Coords.size())
	{
		glm::vec2 direction = glm::normalize(m_Coords.at(m_CurrentDestination) - m_Position);
		velocity = direction * glm::vec2(time * m_Speed);

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

	m_Position += velocity;
}

bool Player::OnKeyPressed(KeyPressedEvent& e)
{
	if (!e.GetRepeatCount() && e.GetKeyCode() == POLY_KEY_E)
	{
		m_Coords.push_back(m_Position);
	}
	return false;
}
