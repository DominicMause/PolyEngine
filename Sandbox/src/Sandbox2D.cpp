#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "PolyEngine/Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2d"), m_CameraController(16.0f / 9.0f)
{}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
	RenderCommand::Clear();

	Renderer2D::BeginScene(m_CameraController.GetCamera());


	for (int y = - grid[0] / 2; y < grid[0]/2; y++)
	{
		for (int x = - grid[1] / 2; x < grid[1] / 2; x++)
		{
			Renderer2D::DrawQuad({ x * 1.11f, y * 1.11f }, { 1.0f, 1.0f }, m_SquareColor);
		}
	}

	Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::DragInt2("Grid Size", grid, 2, 2, 20);
	ImGui::End();
}

void Sandbox2D::OnEvent(Event & event)
{
	m_CameraController.OnEvent(event);
}
