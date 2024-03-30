#include "pepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace PolyEngine
{
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> Texture;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		PE_PROFILE_FUNCTION();
		s_Data = new Renderer2DData();
		s_Data->QuadVertexArray = VertexArray::Create();
		float verticesSquare[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(verticesSquare, sizeof(verticesSquare));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t indiciesSquare[6] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(indiciesSquare, sizeof(indiciesSquare));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);

		s_Data->Texture = Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		s_Data->Texture->SetData(&textureData, sizeof(textureData));
	}

	void Renderer2D::Shutdown()
	{
		PE_PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		PE_PROFILE_FUNCTION();
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		PE_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float rotation)
	{
		DrawQuad({ position.x, position.y, 0 }, size, s_Data->Texture, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float rotation)
	{
		DrawQuad(position, size, s_Data->Texture, color, rotation);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float rotation)
	{
		DrawQuad({ position.x, position.y, 0 }, size, texture, { 1.0f, 1.0f, 1.0f, 1.0f }, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float rotation)
	{
		DrawQuad(position, size, texture, { 1.0f, 1.0f, 1.0f, 1.0f }, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, const float rotation)
	{
		DrawQuad({ position.x, position.y, 0 }, size, texture, color, rotation);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color, const float rotation)
	{
		PE_PROFILE_FUNCTION();
		texture->Bind();
		glm::mat4 transform;
		{
			PE_PROFILE_SCOPE("Calc transform matrix");
			transform = glm::translate(glm::mat4(1.0f), position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1))
				* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1));
		}
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}