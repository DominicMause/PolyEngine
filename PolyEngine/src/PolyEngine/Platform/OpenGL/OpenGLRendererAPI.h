#pragma once

#include "PolyEngine/Renderer/RendererAPI.h"

namespace PolyEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI(){}

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}