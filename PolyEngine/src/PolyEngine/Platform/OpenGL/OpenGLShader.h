#pragma once

#include "PolyEngine/Renderer/Shader.h"
#include "PolyEngine/Renderer/Buffer.h"

#include <glm/glm.hpp>

namespace PolyEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		void UploadUniformInt(std::string name, int value);

		void UploadUniformFloat(std::string name, float value);
		void UploadUniformFloat2(std::string name, const glm::vec2& values);
		void UploadUniformFloat3(std::string name, const glm::vec3& values);
		void UploadUniformFloat4(std::string name, const glm::vec4& values);

		void UploadUniformMat3(std::string name, const glm::mat3& matrix);
		void UploadUniformMat4(std::string name, const glm::mat4& matrix);

		static unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
	private:
		uint32_t m_RendererId;
	};
}