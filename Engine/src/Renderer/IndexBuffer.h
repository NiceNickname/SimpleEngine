#pragma once

namespace Engine {
	
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int* data, unsigned int size);
		virtual void SetData(unsigned int* data, unsigned int size) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual int GetCount() const = 0;
	protected:
		unsigned int m_Count;
	};

}