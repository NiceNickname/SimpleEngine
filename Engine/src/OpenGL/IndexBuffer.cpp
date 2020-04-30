#include "IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(unsigned int* data, unsigned int size)
{
	glGenBuffers(1, &m_Id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	m_Count = size / sizeof(unsigned int);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_Id);
}

void IndexBuffer::SetData(unsigned int* data, unsigned int size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	m_Count = size / sizeof(unsigned int);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
