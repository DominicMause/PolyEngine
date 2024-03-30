#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>



Sandbox2D::Sandbox2D()
	:Layer("Sandbox2d"),
	m_Camera(-(16.0f / 9.0f) * 5, (16.0f / 9.0f) * 5, -5, 5)
{
	m_TexturePlayer = Texture2D::Create("assets/textures/dick.png");
	m_Player = CreateRef<Player>(glm::vec2( 0.0f , 0.0f ), glm::vec2( 1.0f, 1.0f ), m_TexturePlayer);
}

void Sandbox2D::OnAttach()
{
	m_Entities.clear();
	m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
	m_TextureBG = Texture2D::Create("assets/textures/Checkerboard.png");

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
}

void Sandbox2D::OnUpdate(Timestep ts)
{
	PE_PROFILE_FUNCTION();

	// Update
	{
		PE_PROFILE_SCOPE("Update")
		m_Player->Update(ts);
		glm::vec2 pos = m_Player->GetPosition();
		m_Camera.SetPosition({ pos.x, pos.y, 0 });
	}
	// Render
	{
		PE_PROFILE_SCOPE("Render")
		RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
		RenderCommand::Clear();

		Renderer2D::BeginScene(m_Camera);

		Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 19.0f,19.0f }, m_TextureBG);

		for (auto& e : m_Entities)
		{
			Renderer2D::DrawQuad(e.GetPosition(), e.GetSize(), e.GetTexture());
		}

		for (auto& e : m_Player->GetCoords())
		{
			Renderer2D::DrawQuad(e, { 0.1f,0.1f }, { 0.8f,0.3f,0.2f,1.0f });
		}

		Renderer2D::DrawQuad(glm::vec3(0), glm::vec2(1), { 0.8, 0.2, 0.2, 1.0 });
		Renderer2D::DrawQuad(m_Player->GetPosition(), { m_Player->GetRadius() ,m_Player->GetRadius() }, { 0.3f,0.8f,0.2f,1.0f });
		Renderer2D::DrawQuad(m_Player->GetPosition(), m_Player->GetSize(), m_Player->GetTexture(), { 0.3f,0.4f,0.5f,0.75f });


		Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Position %f, %f", m_Player->GetPosition().x, m_Player->GetPosition().y);
	ImGui::End();
}

void Sandbox2D::OnEvent(Event & event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(PE_BIND_EVENT_FN(Sandbox2D::OnWindowResized));
	dispatcher.Dispatch<KeyPressedEvent>(PE_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
	//m_CameraController.OnEvent(event);
}

bool Sandbox2D::OnWindowResized(WindowResizeEvent& e)
{
	float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-aspectRatio * 3, aspectRatio * 3, -3, 3);
	return false;
}

bool Sandbox2D::OnKeyPressed(KeyPressedEvent& e)
{
	m_Player->OnKeyPressed(e);
	return false;
}
