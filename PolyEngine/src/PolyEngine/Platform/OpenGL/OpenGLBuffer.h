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
	private:
		uint32_t m_RendererID;
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