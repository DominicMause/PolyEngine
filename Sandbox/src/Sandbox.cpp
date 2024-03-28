#include <PolyEngine.h>
#include "imgui/imgui.h"
#include <string>
#include <iostream>

using namespace PolyEngine;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		m_Camera = OrtographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
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
			-0.75f, -0.75f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.75f, -0.75f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.75f,  0.75f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f
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

			out vec4 v_Color;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

	void OnUpdate() override
	{
		glm::vec3 position = m_Camera.GetPosition();
		if (Input::IsKeyPressed(POLY_KEY_W))
		{
			position.y += 0.005f;
		}
		if (Input::IsKeyPressed(POLY_KEY_S))
		{
			position.y -= 0.005f;
		}
		if (Input::IsKeyPressed(POLY_KEY_A))
		{
			position.x -= 0.005f;
		}
		if (Input::IsKeyPressed(POLY_KEY_D))
		{
			position.x += 0.005f;
		}
		m_Camera.SetPosition(position);

		RenderCommand::SetClearColor({ 0.1f, 0.075f, 0.075f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);
		Renderer::Submit(m_Shader, m_SquareVertexArray);
		Renderer::Submit(m_Shader, m_VertexArray);
		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("MousePos");
		auto [x, y] = Input::GetMousePosition();
		std::ostringstream stream;
		stream << x << ", " << y;
		ImGui::Text(stream.str().c_str());
		ImGui::End();
	}

	void OnEvent(PolyEngine::Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(PE_BIND_EVENT_FN(ExampleLayer::MouseScrolled));
	}

	bool MouseScrolled(MouseScrolledEvent& event)
	{
		float rotation = m_Camera.GetRotation();
		rotation += (event.GetYOffset() * 0.5f);
		m_Camera.SetRotation(rotation);

		return true;
	}

private:
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<VertexArray> m_SquareVertexArray;
	std::shared_ptr<Shader> m_Shader;
	OrtographicCamera m_Camera;
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