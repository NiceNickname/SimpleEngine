#include "VertexArray.h"


namespace Engine
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_Id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_Id);
	}

	void VertexArray::SetVB(const std::shared_ptr<VertexBuffer>& vb)
	{
		glBindVertexArray(m_Id);
		m_Vbo = vb;
		m_Vbo->Bind();

		VertexBufferLayout layout = m_Vbo->GetLayout();
		unsigned int index = 0;
		for (LayoutElement el : layout.Elements)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, el.GetCount(), el.GetType(), el.normalized, layout.Stride, (const void*)el.offset);
			index++;
		}

	}

	void VertexArray::SetIB(const std::shared_ptr<IndexBuffer>& ib)
	{
		glBindVertexArray(m_Id);
		m_Ibo = ib;
		m_Ibo->Bind();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_Id);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::Draw()
	{
		glDrawElements(GL_TRIANGLES, m_Ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}