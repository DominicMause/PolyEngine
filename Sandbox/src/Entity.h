#pragma once

#include "PolyEngine.h"

using namespace PolyEngine;

class Entity
{
public:
	Entity(const glm::vec2& position,const glm::vec2& size, const Ref<Texture2D>& texture);
	~Entity();

	const glm::vec2& GetPosition() const { return m_Position; }
	const glm::vec2& GetSize() const { return m_Size; }
	const Ref<Texture2D>& GetTexture() const { return m_Texture; }

	void Update(Timestep time);
protected:
	glm::vec2 m_Position = { 0, 0 };
	glm::vec2 m_Size = { 1, 1 };
	Ref<Texture2D> m_Texture;
};