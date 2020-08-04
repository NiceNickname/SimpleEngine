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

		DX11RenderingApi::GetContext()->IASetInputLayout(m_Layout);

		UINT stride = (UINT)m_LayoutDesc.Stride;
		UINT offset = 0;
		DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	}

	void DX11VertexBuffer::Unbind()
	{

	}

	void DX11VertexBuffer::SetData(float* data, unsigned int size)
	{

	}

	// TODO: pass compiled VShader code
	void DX11VertexBuffer::SetLayout(const VertexBufferLayout& layout)
	{
		m_LayoutDesc = layout;

		std::vector<D3D11_INPUT_ELEMENT_DESC> ied;
		ied.resize(m_LayoutDesc.Elements.size());


		for (unsigned int i = 0; i < m_LayoutDesc.Elements.size(); i++)
		{
			ied[i] = { m_LayoutDesc.Elements[i].name.c_str(), 0, (DXGI_FORMAT)m_LayoutDesc.Elements[i].GetType(), 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		}

		

		DX11RenderingApi::GetDevice()->CreateInputLayout(ied.data(), ied.size(), 
			m_VSCode->GetBufferPointer(), m_VSCode->GetBufferSize(), &m_Layout);

		DX11RenderingApi::GetContext()->IASetInputLayout(m_Layout);

		UINT stride = (UINT)m_LayoutDesc.Stride;
		UINT offset = 0;
		DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		
	}

	void DX11VertexBuffer::SetShader(const std::shared_ptr<Shader>& shader)
	{
		m_VSCode = std::static_pointer_cast<DX11Shader>(shader)->GetVSCode();
	}

}