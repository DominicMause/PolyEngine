#include <PolyEngine.h>
#include <PolyEngine/Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"
#include <string>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace PolyEngine;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(16.0f/9.0f)
	{
		m_SquareVertexArray.reset(VertexArray::Create());
		float verticesSquare[4 * 5] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));
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
		squareIB.reset(IndexBuffer::Create(indiciesSquare, sizeof(indiciesSquare)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
		m_TextureUser = Texture2D::Create("assets/textures/user.png");

		std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Timestep ts) override
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
		std::dynamic_pointer_cast<OpenGLShader>(flatShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(flatShader)->UploadUniformFloat3("u_Color", m_SquareColor);

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("FPS %f", 1.0f/m_Ts);
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(PolyEngine::Event& event)
	{
		m_CameraController.OnEvent(event);
	}

private:
	ShaderLibrary m_ShaderLibrary;
	Ref<VertexArray> m_SquareVertexArray;

	Ref<Texture2D> m_Texture;
	Ref<Texture2D> m_TextureUser;	

	OrthographicCameraController m_CameraController;

	Timestep m_Ts = 0;

	glm::vec3 m_SquareColor = { 0.8f, 0.2f, 0.3f };
};

class Sandbox : public Application 
{
public: 
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() 
	{

	}

};

PolyEngine::Application* PolyEngine::CreateApplication()
{
	return new Sandbox();
}