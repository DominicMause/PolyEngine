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

	m_PropsBG.Position.z = -0.1f;
	m_PropsBG.Size = { 19, 19 };
	m_PropsBG.Texture = m_TextureBG;

	m_PropsPlayer.Texture = m_TexturePlayer;

	m_PropsBox.Texture = m_Texture;

	m_PropsCoord.Size = { 0.1f,0.1f };
	m_PropsCoord.Color = { 0.8f,0.3f,0.2f,0.5f };
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

		Renderer2D::DrawQuad(m_PropsBG);

		for (auto& e : m_Entities)
		{
			m_PropsBox.Position = glm::vec3(e.GetPosition(),0);
			Renderer2D::DrawQuad(m_PropsBox);
		}

		for (auto& e : m_Player.GetCoords())
		{
			m_PropsCoord.Position = glm::vec3(e, 1);
			Renderer2D::DrawQuad(m_PropsCoord);
		}

		m_PropsPlayer.Position = glm::vec3(m_Player.GetPosition(),1);
		Renderer2D::DrawQuad(m_PropsPlayer);


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
