#include "pepch.h"
#include "Texture.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLTexture.h"

namespace PolyEngine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}
}