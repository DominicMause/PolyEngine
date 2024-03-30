#include "pepch.h"
#include "GraphicsContext.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLContext.h"

namespace PolyEngine
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}