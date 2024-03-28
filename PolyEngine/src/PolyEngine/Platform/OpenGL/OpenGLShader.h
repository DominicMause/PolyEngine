#pragma once

#include "PolyEngine/Renderer/Shader.h"
#include "PolyEngine/Renderer/Buffer.h"

namespace PolyEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;
		
		virtual void SetUniformMat4(std::string name, const glm::mat4& matrix) const override;

		static unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
	private:
		uint32_t m_RendererId;
	};
}