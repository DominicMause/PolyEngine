#include "pepch.h"
#include "RenderCommand.h"

namespace PolyEngine
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}