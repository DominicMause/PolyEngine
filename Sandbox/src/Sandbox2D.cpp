#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>



Sandbox2D::Sandbox2D()
	:Layer("Sandbox2d"), m_Player(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f))
{}

void Sandbox2D::OnAttach()
{
	PE_PROFILE_FUNCTION();
	m_Entities.clear();
	m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
	m_TexturePlayer = Texture2D::Create("assets/textures/dick.png");
	m_TextureBG = Texture2D::Create("assets/textures/Checkerboard.png");

	m_Player.SetTexture(m_TexturePlayer);

	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{
			if (y == -10 || y == 10 || x == -10 || x == 10)
			{
				m_Entities.push_back(Entity({ x, y }, { 1.0f, 1.0f }, m_Texture));
			}
		}
	}
}

void Sandbox2D::OnDetach()
{
	PE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Timestep ts)
{
	PE_PROFILE_FUNCTION();

	// Update
	{
		PE_PROFILE_SCOPE("Update")
		m_Player.Update(ts);
	}
	// Render
	{
		PE_PROFILE_SCOPE("Render")
		RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_Player.GetCamera());

		Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 19.0f,19.0f }, m_TextureBG);

		for (auto& e : m_Entities)
		{
			Renderer2D::DrawQuad(e.GetPosition(), e.GetSize(), e.GetTexture());
		}

		for (auto& e : m_Player.GetCoords())
		{
			Renderer2D::DrawQuad(e, { 0.1f,0.1f }, { 0.8f,0.3f,0.2f,1.0f });
		}

		Renderer2D::DrawQuad(glm::vec3(0), glm::vec2(1), { 0.8, 0.2, 0.2, 1.0 });
		Renderer2D::DrawQuad(m_Player.GetPosition(), { m_Player.GetRadius() ,m_Player.GetRadius() }, { 0.3f,0.8f,0.2f,1.0f });
		Renderer2D::DrawQuad(m_Player.GetPosition(), m_Player.GetSize(), m_Player.GetTexture());


		Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Position %f, %f", m_Player.GetPosition().x, m_Player.GetPosition().y);
	ImGui::End();
}

void Sandbox2D::OnEvent(Event & event)
{
	m_Player.OnEvent(event);
}
