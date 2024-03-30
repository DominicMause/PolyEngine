#include "pepch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace PolyEngine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}

		PE_CORE_ERROR("Shadertype {0} not supproted!", type);
		return 0;
	}

	GLenum OpenGLShader::ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		PE_CORE_ASSERT(false, "Unkown ShaderDataType");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);

		Compile(shaderSources);

		// Getting Name from File 
		// assets/shaders/Texture.shader.glsl -> Texture.shader
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			PE_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			PE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			PE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			PE_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = 
				(pos == std::string::npos) ? 
				source.substr(nextLinePos) : 
				source.substr(nextLinePos, pos - nextLinePos);
		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLint programm = glCreateProgram();
		PE_CORE_ASSERT(shaderSources.size() <= 2, "Only two shaders supported!");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* src = source.c_str();
			glShaderSource(shader, 1, &src, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				PE_CORE_ERROR("{0}", infoLog.data());
				PE_CORE_ASSERT(false, "Shader compilation failure!");
				return;
			}

			glAttachShader(programm, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(programm);
		GLint isLinked = 0;
		glGetProgramiv(programm, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programm, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programm, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(programm);

			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			PE_CORE_ERROR("{0}", infoLog.data());
			PE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(programm, id);
			glDeleteShader(id);
		}

		m_RendererId = programm;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4 & value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetInt(const std::string& name, const int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4 & value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(position, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(position, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(position, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(position, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(position, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(position, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		uint32_t position = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}