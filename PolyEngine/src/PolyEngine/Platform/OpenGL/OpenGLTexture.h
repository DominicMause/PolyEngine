#pragma once
#include "PolyEngine/Renderer/Texture.h"
#include <glad/glad.h>

namespace PolyEngine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual void SetData(void* data, uint32_t size) override;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;

		uint32_t m_RendererID;
		uint32_t m_Width;
		uint32_t m_Height;

		GLenum m_InternalFormat, m_DataFormat;
	};
}