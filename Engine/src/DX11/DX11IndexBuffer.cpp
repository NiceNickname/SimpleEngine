#include "pch.h"

#include "DX11IndexBuffer.h"
#include "DX11RenderingApi.h"

namespace Engine {

	DX11IndexBuffer::DX11IndexBuffer(unsigned int* data, unsigned int size)
	{
		D3D11_BUFFER_DESC bd;

		m_Count = size / sizeof(unsigned int);

		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &m_IndexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		DX11RenderingApi::GetContext()->Map(m_IndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, data, size);
		DX11RenderingApi::GetContext()->Unmap(m_IndexBuffer, NULL);

		DX11RenderingApi::GetContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	DX11IndexBuffer::~DX11IndexBuffer()
	{
		m_IndexBuffer->Release();
	}

	void DX11IndexBuffer::SetData(unsigned int* data, unsigned int size)
	{

	}

	void DX11IndexBuffer::Bind()
	{
		DX11RenderingApi::GetContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void DX11IndexBuffer::Unbind()
	{

	}

	int DX11IndexBuffer::GetCount() const
	{
		return m_Count;
	}

}