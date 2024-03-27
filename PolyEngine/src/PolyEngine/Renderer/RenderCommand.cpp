#include "pepch.h"
#include "RenderCommand.h"

#include "PolyEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace PolyEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}