#include "pepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "PolyEngine/Platform/OpenGL/OpenGLShader.h"

namespace PolyEngine
{
	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------------ Shader -------------------------------------------------
	// ---------------------------------------------------------------------------------------------------

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filepath);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		PE_CORE_ASSERT(false, "Renderer not supported");
		return nullptr;
	}

	// ---------------------------------------------------------------------------------------------------
	// -------------------------------------- Shader Libary ----------------------------------------------
	// ---------------------------------------------------------------------------------------------------

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		PE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		PE_CORE_TRACE("Added Shader: {0}", name);
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		PE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}