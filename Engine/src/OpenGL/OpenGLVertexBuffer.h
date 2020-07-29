#pragma once
#include "Renderer/VertexBufferLayout.h"

namespace Engine
{
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, unsigned int size);
		~OpenGLVertexBuffer();
		void SetData(float* data, unsigned int size);
		void SetLayout(const VertexBufferLayout& layout);
		void Bind();
		void Unbind();
		inline VertexBufferLayout GetLayout() { return m_Layout; }

	private:
		unsigned int m_Id;
		VertexBufferLayout m_Layout = {};
	};
}