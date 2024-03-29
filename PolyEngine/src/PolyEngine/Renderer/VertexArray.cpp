#include "pepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace PolyEngine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}