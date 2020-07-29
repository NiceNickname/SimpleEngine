#pragma once


namespace Engine
{
	class OpenGLIndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* data, unsigned int size);
		~OpenGLIndexBuffer();
		void SetData(unsigned int* data, unsigned int size);
		void Bind();
		void Unbind();
		inline int GetCount() const { return m_Count; }
	private:
		unsigned int m_Id, m_Count;

	};
}