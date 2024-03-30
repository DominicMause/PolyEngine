#include "Sandbox3D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D()
: Layer("Sandbox3D"), m_CameraController(16.0f / 9.0f)
{
	m_SquareVertexArray = VertexArray::Create();
	float verticesSquare[4 * 5] = {
		-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
	};
	Ref<VertexBuffer> squareVB;
	squareVB = VertexBuffer::Create(verticesSquare, sizeof(verticesSquare));
	squareVB->SetLayout({
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVertexArray->AddVertexBuffer(squareVB);

	uint32_t indiciesSquare[6] = {
		0, 1, 2,
		2, 3, 0
	};
	Ref<IndexBuffer> squareIB;
	squareIB = IndexBuffer::Create(indiciesSquare, sizeof(indiciesSquare));
	m_SquareVertexArray->SetIndexBuffer(squareIB);

	m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
	m_TextureUser = Texture2D::Create("assets/textures/user.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void Sandbox3D::OnAttach()
{

}

void Sandbox3D::OnDetach()
{

}

void Sandbox3D::OnUpdate(Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);
	m_Ts = ts;

	//Render
	RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
	RenderCommand::Clear();

	Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	auto flatShader = m_ShaderLibrary.Get("FlatColor");
	flatShader->Bind();
	flatShader->SetFloat3("u_Color", m_SquareColor);

	m_TextureUser->Bind();
	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Renderer::Submit(flatShader, m_SquareVertexArray, transform);
		}
	}


	auto textureShader = m_ShaderLibrary.Get("Texture");
	m_Texture->Bind();
	Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	m_TextureUser->Bind();
	Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("FPS %f", 1.0f / m_Ts);
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox3D::OnEvent(Event & event)
{
	m_CameraController.OnEvent(event);
}
