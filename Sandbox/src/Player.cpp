#include "Player.h"

Player::Player(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	: Entity(position, size, texture)
{}

void Player::Update(Timestep time, std::vector<Entity>& colliders)
{
	bool wasGrounded = m_IsGrounded;
	m_IsGrounded = false;
	glm::vec2 velocity = { 0,0 };

	if (Input::IsKeyPressed(POLY_KEY_A))
	{
		velocity.x -= m_Speed * time;
	}
	if (Input::IsKeyPressed(POLY_KEY_D))
	{
		velocity.x += m_Speed * time;
	}

	if (wasGrounded && Input::IsKeyPressed(POLY_KEY_SPACE))
	{
		velocity.y += 40 * time;
	}

	if (!wasGrounded)
	{
		velocity.y -= 3.0f * time;
	}

	for (auto& collider : colliders)
	{
		glm::vec2 pos = collider.GetPosition();
		glm::vec2 size = collider.GetSize();
		if (
			m_Position.x + m_Size.x / 2 + 0.1f >= pos.x + size.x / 2 &&
			m_Position.x - m_Size.x / 2 - 0.1f <= pos.x + size.x / 2 &&
			m_Position.y + m_Size.y / 2 + 0.1f >= pos.y - size.y / 2 &&
			m_Position.y - m_Size.y / 2 - 0.1f <= pos.y + size.y / 2
			)
		{
			if (velocity.y <= 0)
			{
				m_Position.y = pos.y + size.y / 2 + m_Size.y / 2;
				velocity.y = 0;
				m_IsGrounded = true;
			}
			else if (velocity.y > 0)
			{
				m_Position.y = pos.y - size.y / 2 - m_Size.y / 2 - 0.01f; // Kleinen Offset hinzufügen
				velocity.y = 0;
			}
			
		}
	}
	m_Position += velocity;
}
