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
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_Camera.SetPosition(glm::vec3(0,0,-1));
		
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

		m_Shader.reset(Shader::Create("assets/shaders/FlatColor.glsl"));
		m_TextureShader.reset(Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Texture2D::Create("assets/textures/container_diffuse.png");
		m_TextureUser = Texture2D::Create("assets/textures/user.png");

		std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Timestep ts) override
	{
		m_Ts = ts;
		MoveCamera(ts);

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotaion);

		RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = -10; y <= 10; y++)
		{
			for (int x = -10; x <= 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Renderer::Submit(m_Shader, m_SquareVertexArray, transform);
			}
		}

		m_Texture->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_TextureUser->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("FPS %f", 1.0f/m_Ts);
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat("Movement Speed", &m_CameraSpeed, 0, 50);
		bool resetPos = ImGui::Button("Reset Position");
		if (resetPos)
		{
			m_CameraPosition = glm::vec3(0);
			m_CameraRotaion = 0;
		}
		ImGui::End();
	}

	void OnEvent(PolyEngine::Event& event)
	{
		
	}

	void MoveCamera(Timestep ts)
	{
		if (Input::IsKeyPressed(POLY_KEY_W))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_S))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_A))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_D))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
		}

		if (Input::IsKeyPressed(POLY_KEY_Q))
		{
			m_CameraRotaion += m_RotationSpeed * ts;
		}
		if (Input::IsKeyPressed(POLY_KEY_E))
		{
			m_CameraRotaion -= m_RotationSpeed * ts;
		}
	}

private:
	Ref<VertexArray> m_SquareVertexArray;
	Ref<Shader> m_Shader;
	Ref<Shader> m_TextureShader;
	OrtographicCamera m_Camera;

	Ref<Texture2D> m_Texture;
	Ref<Texture2D> m_TextureUser;

	glm::vec3 m_CameraPosition = glm::vec3(0.0f);
	float m_CameraRotaion = 0;
	float m_CameraSpeed = 5.0f;
	float m_RotationSpeed = 180.0f;
	
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