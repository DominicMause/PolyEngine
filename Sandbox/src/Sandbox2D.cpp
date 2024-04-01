#include "Sandbox2D.h"

#include <random>

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

static float GetRandom()
{
	static std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	return distribution(generator);
}

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2d"), m_CameraController(16.0f / 9.0f)
{}

void Sandbox2D::OnAttach()
{
	PE_PROFILE_FUNCTION();

	m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
	m_TexturePlayer = Texture2D::Create("assets/textures/dick.png");
	m_TextureBG = Texture2D::Create("assets/textures/Checkerboard.png");

	m_PropsBG.Rotation = 5;
	m_PropsBG.Position.z = -0.1f;
	m_PropsBG.Size = { 19, 19 };
	m_PropsBG.Texture = m_TextureBG;

	m_PropsPlayer.Color = { 1.0f, 0.8f, 0.8f, 1.0f };
	m_PropsBG.Texture = m_TexturePlayer;

	m_PropsCoord.Size = { 1.0f, 1.0f };
	m_PropsCoord.Texture = m_Texture;

	m_Entities.clear();

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
			m_CameraController.OnUpdate(ts);
	}
	// Render
	{
		PE_PROFILE_SCOPE("Render")
			RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (int y = 0; y < 100; y++)
		{
			for (int x = 0; x < 100; x++)
			{
				m_PropsCoord.Position = glm::vec3(x, y, 0);
				m_PropsCoord.Color = glm::vec4(GetRandom(), GetRandom(), GetRandom(), 1.0f);

				Renderer2D::DrawQuad(m_PropsCoord);
			}
		}

		Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::End();
}

void Sandbox2D::OnEvent(Event& event)
{
	m_CameraController.OnEvent(event);
	//m_Player.OnEvent(event);
}
