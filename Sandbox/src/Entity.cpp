#include "Entity.h"

Entity::Entity(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	: m_Position(position), m_Size(size), m_Texture(texture)
{}

Entity::~Entity()
{}

void Entity::Update(Timestep time)
{}
