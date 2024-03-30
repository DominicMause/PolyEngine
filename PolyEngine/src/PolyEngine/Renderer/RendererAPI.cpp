#include "pepch.h"
#include "RendererAPI.h"
#include "PolyEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace PolyEngine
{
	
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}