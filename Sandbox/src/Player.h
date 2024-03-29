#pragma once

#include "PolyEngine.h"
#include "Entity.h"

using namespace PolyEngine;

class Player : public Entity
{
public:
	Player() {}
	Player(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	void Update(Timestep time, std::vector<Entity>& colliders);
private:
	bool m_IsGrounded = false;
	float m_Speed = 10;
};