#pragma once

#include "PolyEngine/Renderer/Shader.h"

namespace PolyEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

	private:
		uint32_t m_RendererId;
	};
}