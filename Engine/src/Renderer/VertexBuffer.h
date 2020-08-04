#pragma once
#include "VertexBufferLayout.h"
#include "Shader.h"

namespace Engine
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* data, unsigned int size);

		virtual void SetLayout(const VertexBufferLayout& layout) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(float* data, unsigned int size) = 0;
		virtual void SetShader(const std::shared_ptr<Shader>& shader) {} ;
		virtual VertexBufferLayout GetLayout() = 0;
	};
}