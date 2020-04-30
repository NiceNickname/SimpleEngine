#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void SetVB(VertexBuffer* vb);
	void SetIB(IndexBuffer* ib);
	void Bind();
	void Unbind();
	void Draw();
private:
	unsigned int m_Id;
	VertexBuffer* m_Vbo;
	IndexBuffer* m_Ibo;
};
