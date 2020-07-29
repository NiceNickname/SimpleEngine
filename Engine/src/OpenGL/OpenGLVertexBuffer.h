#pragma once
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/VertexBuffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, unsigned int size);
		~OpenGLVertexBuffer();
		void SetData(float* data, unsigned int size);
		virtual void SetLayout(const VertexBufferLayout& layout) override;
		void Bind();
		void Unbind();
		inline VertexBufferLayout GetLayout() { return m_Layout; }

	private:
		unsigned int m_Id;
		VertexBufferLayout m_Layout = {};
	};
}