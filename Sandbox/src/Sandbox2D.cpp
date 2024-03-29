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


	for (int y = -m_Grid[0] / 2; y < m_Grid[0]/2; y++)
	{
		for (int x = -m_Grid[1] / 2; x < m_Grid[1] / 2; x++)
		{
			Renderer2D::DrawQuad({ x * m_Spacing, y * m_Spacing }, { 1.0f, 1.0f }, m_SquareColor, m_Rotation);
		}
	}

	Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::SliderInt2("Grid Size", m_Grid, 2, 20);
	ImGui::SliderFloat("Rotation", &m_Rotation, 0, 360);
	ImGui::SliderFloat("Spacing", &m_Spacing, 0, 10);
	ImGui::End();
}

void Sandbox2D::OnEvent(Event & event)
{
	m_CameraController.OnEvent(event);
}
