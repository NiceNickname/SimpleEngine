#pragma once
#include "Renderer/VertexBuffer.h"

namespace Engine {

	class DX11VertexBuffer : public VertexBuffer
	{
	public:
		DX11VertexBuffer(float* data, unsigned int size);
		~DX11VertexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetData(float* data, unsigned int size) override;
		virtual void SetLayout(const VertexBufferLayout& layout) override;
		virtual inline VertexBufferLayout GetLayout() override { return m_LayoutDesc; };

	private:
		ID3D11Buffer* m_VertexBuffer;
		VertexBufferLayout m_LayoutDesc = {};
		ID3D11InputLayout* m_Layout;
	};

}