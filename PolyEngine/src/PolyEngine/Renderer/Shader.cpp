#include "pepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLShader.h"

namespace PolyEngine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}