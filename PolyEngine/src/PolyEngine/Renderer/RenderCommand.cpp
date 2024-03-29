#include "pepch.h"
#include "RenderCommand.h"

#include "PolyEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace PolyEngine
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}