#pragma once

#include "PolyEngine/Renderer/Shader.h"
#include "PolyEngine/Renderer/Buffer.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace PolyEngine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }
		
		void UploadUniformInt(std::string name, int value);

		void UploadUniformFloat(std::string name, float value);
		void UploadUniformFloat2(std::string name, const glm::vec2& values);
		void UploadUniformFloat3(std::string name, const glm::vec3& values);
		void UploadUniformFloat4(std::string name, const glm::vec4& values);

		void UploadUniformMat3(std::string name, const glm::mat3& matrix);
		void UploadUniformMat4(std::string name, const glm::mat4& matrix);

		static unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererId;
		std::string m_Name;
	};
}