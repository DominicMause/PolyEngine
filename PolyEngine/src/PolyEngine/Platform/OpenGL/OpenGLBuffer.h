#pragma once

#include "PolyEngine/Renderer/Buffer.h"

namespace PolyEngine
{
	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------ OpenGL Vertex Buffer -----------------------------------------
	// ---------------------------------------------------------------------------------------------------

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_BufferLayout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;
	};

	// ---------------------------------------------------------------------------------------------------
	// ------------------------------------ OpenGL Index Buffer ------------------------------------------
	// ---------------------------------------------------------------------------------------------------

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}