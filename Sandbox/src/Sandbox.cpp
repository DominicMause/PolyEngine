#include <PolyEngine.h>
#include "imgui/imgui.h"
#include <string>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

using namespace PolyEngine;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_Camera.SetPosition(glm::vec3(0,0,-1));
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indicies[3] = {
			0, 1, 2
		};
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indicies, 6));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(VertexArray::Create());
		float verticesSquare[4 * 7] = {
			-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));
		squareVB->SetLayout(layout);
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t indiciesSquare[6] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(indiciesSquare, sizeof(indiciesSquare)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Timestep ts) override
	{
		MoveCamera(ts);

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotaion);

		RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Renderer::Submit(m_Shader, m_SquareVertexArray, transform);
			}
		}
		Renderer::Submit(m_Shader, m_VertexArray);
		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
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
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<VertexArray> m_SquareVertexArray;
	std::shared_ptr<Shader> m_Shader;
	OrtographicCamera m_Camera;

	glm::vec3 m_CameraPosition = glm::vec3(0.0f);
	float m_CameraRotaion = 0;
	float m_CameraSpeed = 5.0f;
	float m_RotationSpeed = 180.0f;
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