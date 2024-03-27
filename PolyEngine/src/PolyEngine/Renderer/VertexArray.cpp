#include "pepch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace PolyEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}