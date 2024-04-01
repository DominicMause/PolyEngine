#include "pepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace PolyEngine
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> Texture;

		uint32_t QuadIndexCount = 0;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;
	};

	static Renderer2DData s_Data;

	

	void Renderer2D::Init()
	{
		PE_PROFILE_FUNCTION();
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float,  "a_TextureID"},
			{ ShaderDataType::Float,  "a_TilingFactor"}
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.Texture = Texture2D::Create(1, 1);
		uint32_t textureData = 0xffffffff;
		s_Data.Texture->SetData(&textureData, sizeof(textureData));

		int32_t sampler[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			sampler[i] = i;

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", sampler, s_Data.MaxTextureSlots);

		s_Data.TextureSlots[0] = s_Data.Texture;
	}

	void Renderer2D::Shutdown()
	{
		PE_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		PE_PROFILE_FUNCTION();
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		PE_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		//Bind Textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);
		
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const RenderProps& renderProps)
	{
		PE_PROFILE_FUNCTION();

		float textureIndex = 0.0f;

		if (renderProps.Texture)
		{
			for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
			{
				//get() to get the pointer, & to deref
				if (*s_Data.TextureSlots[i].get() == *renderProps.Texture.get())
				{
					textureIndex = (float)i;
					break;
				}
			}

			if (textureIndex == 0.0f)
			{
				textureIndex = (float)s_Data.TextureSlotIndex;
				s_Data.TextureSlots[s_Data.TextureSlotIndex] = renderProps.Texture;
				s_Data.TextureSlotIndex++;
			}
		}

		s_Data.QuadVertexBufferPtr->Position = renderProps.Position;
		s_Data.QuadVertexBufferPtr->Color = renderProps.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex; 
		s_Data.QuadVertexBufferPtr->TilingFactor = renderProps.TilingFactor;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { renderProps.Position.x + renderProps.Size.x,renderProps.Position.y,renderProps.Position.z };
		s_Data.QuadVertexBufferPtr->Color = renderProps.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = renderProps.TilingFactor;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { renderProps.Position.x + renderProps.Size.x,renderProps.Position.y + renderProps.Size.y,renderProps.Position.z };
		s_Data.QuadVertexBufferPtr->Color = renderProps.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = renderProps.TilingFactor;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { renderProps.Position.x,renderProps.Position.y + renderProps.Size.y,renderProps.Position.z };
		s_Data.QuadVertexBufferPtr->Color = renderProps.Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr->TilingFactor = renderProps.TilingFactor;
		s_Data.QuadVertexBufferPtr++;

		//s_Data.TextureShader->SetFloat("u_TilingFactor", renderProps.TilingFactor);

		/*if (renderProps.Rotation)
		{
			DrawRotatedQuad(renderProps);
		}
		else
		{
			DrawNormalQuad(renderProps);
		}*/
		s_Data.QuadIndexCount += 6;
	}

	void Renderer2D::DrawRotatedQuad(const RenderProps& renderProps)
	{
		PE_PROFILE_FUNCTION();
		glm::mat4 transform;
		{
			PE_PROFILE_SCOPE("Calc transform rotated matrix");
			transform = glm::translate(glm::mat4(1.0f), renderProps.Position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(renderProps.Rotation), glm::vec3(0, 0, 1))
				* glm::scale(glm::mat4(1.0f), glm::vec3(renderProps.Size, 1));
		}
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawNormalQuad(const RenderProps & renderProps)
	{
		PE_PROFILE_FUNCTION();
		glm::mat4 transform;
		{
			PE_PROFILE_SCOPE("Calc transform normal matrix");
			transform = glm::translate(glm::mat4(1.0f), renderProps.Position)
				* glm::scale(glm::mat4(1.0f), glm::vec3(renderProps.Size, 1));
		}
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}
}