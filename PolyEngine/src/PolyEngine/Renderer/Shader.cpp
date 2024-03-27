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
		case RendererAPI::None:
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		return nullptr;
	}
}