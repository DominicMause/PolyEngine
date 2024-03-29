#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "PolyEngine/Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2d"), m_CameraController(16.0f / 9.0f)
{}

void Sandbox2D::OnAttach()
{
	m_VertexArray = VertexArray::Create();
	float verticesSquare[3 * 4] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
	};
	Ref<VertexBuffer> squareVB;
	squareVB = VertexBuffer::Create(verticesSquare, sizeof(verticesSquare));
	squareVB->SetLayout({
		{ ShaderDataType::Float3, "a_Position" },
		});
	m_VertexArray->AddVertexBuffer(squareVB);

	uint32_t indiciesSquare[6] = {
		0, 1, 2,
		2, 3, 0
	};
	Ref<IndexBuffer> squareIB;
	squareIB = IndexBuffer::Create(indiciesSquare, sizeof(indiciesSquare));
	m_VertexArray->SetIndexBuffer(squareIB);

	m_Shader = Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach(){}

void Sandbox2D::OnUpdate(Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	// Render
	RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
	RenderCommand::Clear();

	Renderer::BeginScene(m_CameraController.GetCamera());
	std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	for (int y = - grid[0] / 2; y < grid[0]/2; y++)
	{
		for (int x = - grid[1] / 2; x < grid[1] / 2; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Renderer::Submit(m_Shader, m_VertexArray, transform);
		}
	}

	Renderer::EndScene();
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
