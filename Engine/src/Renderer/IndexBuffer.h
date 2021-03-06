#pragma once

namespace Engine {
	
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(void* data, unsigned int size);
		virtual void SetData(void* data, unsigned int size) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual int GetCount() const = 0;
	protected:
		unsigned int m_Count;
	};

}