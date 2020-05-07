#pragma once
#include <memory>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void SetVB(const std::shared_ptr<VertexBuffer>& vb);
		void SetIB(const std::shared_ptr<IndexBuffer>& ib);
		void Bind();
		void Unbind();
		void Draw();
	private:
		unsigned int m_Id;
		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ibo;
	};
}