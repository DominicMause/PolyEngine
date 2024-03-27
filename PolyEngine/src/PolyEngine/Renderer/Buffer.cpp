#include "pepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace PolyEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}