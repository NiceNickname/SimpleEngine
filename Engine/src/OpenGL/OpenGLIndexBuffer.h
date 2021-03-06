#pragma once
#include "Renderer/IndexBuffer.h"

namespace Engine
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(void* data, unsigned int size);
		~OpenGLIndexBuffer();
		virtual void SetData(void* data, unsigned int size) override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual inline int GetCount() const override { return m_Count; } 
	private:
		unsigned int m_Id;
	};
}