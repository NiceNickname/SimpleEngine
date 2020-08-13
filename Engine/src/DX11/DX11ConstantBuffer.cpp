#include "pch.h"

#include "DX11ConstantBuffer.h"

namespace Engine {



	DX11ConstantBuffer::DX11ConstantBuffer(const std::string& name, unsigned int bytewidth)
		: m_Name(name)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = bytewidth;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &m_Buffer);
		DX11RenderingApi::GetContext()->VSSetConstantBuffers(0, 1, &m_Buffer);
	}

	DX11ConstantBuffer::~DX11ConstantBuffer()
	{
		m_Buffer->Release();
	}

	void DX11ConstantBuffer::Update(const void* data)
	{
		DX11RenderingApi::GetContext()->UpdateSubresource(m_Buffer, 0, 0, data, 0, 0);
	}

	void DX11ConstantBuffer::Bind(unsigned int slot)
	{
		DX11RenderingApi::GetContext()->VSSetConstantBuffers(slot, 1, &m_Buffer);
	}

}