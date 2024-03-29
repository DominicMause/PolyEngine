#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "PolyEngine/Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2d"),
	m_Camera(-(16.0f / 9.0f) * 3, (16.0f / 9.0f) * 3, -3, 3)
{
	m_TexturePlayer = Texture2D::Create("assets/textures/user.png");
	m_Player = Player({ 0.0f , 10.0f }, { 1.0f, 1.0f }, m_TexturePlayer);
}

void Sandbox2D::OnAttach()
{
	m_Entities.clear();
	m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
	m_TextureBG = Texture2D::Create("assets/textures/Checkerboard.png");

	for (int x = -10; x < 10; x++)
	{
		m_Entities.push_back(Entity({ x, -2 }, { 1.0f, 1.0f }, m_Texture));
	}
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Timestep ts)
{
	// Update
	m_Player.Update(ts, m_Entities); 
	glm::vec2 pos = m_Player.GetPosition();
	m_Camera.SetPosition({pos.x, pos.y, 0});
	
	// Render
	RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
	RenderCommand::Clear();

	Renderer2D::BeginScene(m_Camera);

	for (auto& e : m_Entities)
	{
		Renderer2D::DrawQuad(e.GetPosition(), e.GetSize(), e.GetTexture());
	}

	Renderer2D::DrawQuad(m_Player.GetPosition(), m_Player.GetSize(), m_Player.GetTexture());
	Renderer2D::DrawQuad({ 0.0f,0.0f,- 0.1f }, { 10.0f,10.0f }, m_TextureBG);
	
	Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Position %f, %f", m_Player.GetPosition().x, m_Player.GetPosition().y);
	ImGui::End();
}

void Sandbox2D::OnEvent(Event & event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(PE_BIND_EVENT_FN(Sandbox2D::OnWindowResized));
	//m_CameraController.OnEvent(event);
}

bool Sandbox2D::OnWindowResized(WindowResizeEvent& e)
{
	float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-aspectRatio * 3, aspectRatio * 3, -3, 3);
	return false;
}
