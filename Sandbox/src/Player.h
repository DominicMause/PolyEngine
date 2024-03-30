#pragma once

#include "PolyEngine.h"
#include "Entity.h"

using namespace PolyEngine;

class Player : public Entity
{
public:
	Player(const glm::vec2& position, const glm::vec2& size);
	void Update(Timestep time);

	void OnEvent(Event& e);
	const OrthographicCamera& GetCamera() const { return m_Camera; }
	OrthographicCamera& GetCamera() { return m_Camera; }

	std::vector<glm::vec2>& GetCoords() { return m_Coords; }
	float GetRadius() const { return m_Radius; }
private:
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);
private:
	float m_Speed = 5;
	float m_ZoomLevel = 6.0f;
	OrthographicCamera m_Camera;

	float m_Radius = 0.1f;
	bool m_IsAutoMode = false;
	std::vector<glm::vec2> m_Coords;
	uint32_t m_CurrentDestination = 0;
};