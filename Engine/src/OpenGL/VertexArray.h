#pragma once
#include <memory>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void SetVB(const std::shared_ptr<OpenGLVertexBuffer>& vb);
		void SetIB(const std::shared_ptr<OpenGLIndexBuffer>& ib);
		void Bind();
		void Unbind();
		void Draw();
	private:
		unsigned int m_Id;
		std::shared_ptr<OpenGLVertexBuffer> m_Vbo;
		std::shared_ptr<OpenGLIndexBuffer> m_Ibo;
	};
}