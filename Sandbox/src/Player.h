#pragma once

#include "PolyEngine.h"
#include "Entity.h"

using namespace PolyEngine;

class Player : public Entity
{
public:
	Player() {}
	Player(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	void Update(Timestep time);
	bool OnKeyPressed(KeyPressedEvent& e);

	std::vector<glm::vec2>& GetCoords() { return m_Coords; }
	float GetRadius() { return m_Radius; }
private:
	bool m_IsAutoMode = false;
	float m_Speed = 5;
	uint32_t m_CurrentDestination = 0;

	float m_Radius = 0.1;
	std::vector<glm::vec2> m_Coords;
};