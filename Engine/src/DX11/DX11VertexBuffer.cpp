#include "pch.h"
#include "DX11VertexBuffer.h"

namespace Engine {



	DX11VertexBuffer::DX11VertexBuffer(float* data, unsigned int size)
	{
		// vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		DX11RenderingApi::GetContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, data, size);
		DX11RenderingApi::GetContext()->Unmap(m_VertexBuffer, NULL);

	}
	
	DX11VertexBuffer::~DX11VertexBuffer()
	{
		m_VertexBuffer->Release();
		m_Layout->Release();
	}

	void DX11VertexBuffer::Bind()
	{

		UINT stride = m_LayoutDesc.Stride;
		UINT offset = 0;
		DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		DX11RenderingApi::GetContext()->IASetInputLayout(m_Layout);
	}

	void DX11VertexBuffer::Unbind()
	{

	}

	void DX11VertexBuffer::SetData(float* data, unsigned int size)
	{

	}

	void DX11VertexBuffer::SetLayout(const VertexBufferLayout& layout)
	{
		D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		/*m_LayoutDesc = layout;

		for (int i = 0; i < layout.Elements.size())
		{
			ied[i] = {layout.Elements[i].name, 0, layout.Elements[i].GetType(), 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0};
		}*/

		UINT stride = sizeof(float) * 3;
		UINT offset = 0;
		DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		DX11RenderingApi::GetDevice()->CreateInputLayout(ied, sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC), 
			DX11RenderingApi::GetVSCode()->GetBufferPointer(), DX11RenderingApi::GetVSCode()->GetBufferSize(), &m_Layout);

		DX11RenderingApi::GetContext()->IASetInputLayout(m_Layout);

		
	}

}