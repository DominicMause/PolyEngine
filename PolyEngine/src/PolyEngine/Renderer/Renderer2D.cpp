#include "pepch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "PolyEngine/Platform/OpenGL/OpenGLShader.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace PolyEngine
{
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();
		s_Data->QuadVertexArray = VertexArray::Create();
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
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t indiciesSquare[6] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(indiciesSquare, sizeof(indiciesSquare));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera & camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position,const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0 }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position,const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;

		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}