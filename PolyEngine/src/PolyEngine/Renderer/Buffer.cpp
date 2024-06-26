#include "pepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace PolyEngine
{
	Ref<VertexBuffer> VertexBuffer::Create(size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
		return Ref<VertexBuffer>();
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}