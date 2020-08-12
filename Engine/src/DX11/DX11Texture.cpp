#include "pch.h"

#include "DX11RenderingApi.h"
#include "DX11Texture.h"

#include <stb_image.h>

namespace Engine {

	unsigned int DX11Texture::id = 1;

	DX11Texture::DX11Texture(const std::string& path)
	{
		m_Id = id;
		id++;

		stbi_uc* data = nullptr;

		data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);

		D3D11_TEXTURE2D_DESC texd = {};
		texd.Width = m_Width;
		texd.Height = m_Height;
		texd.MipLevels = 1;
		texd.ArraySize = 1;
		texd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texd.SampleDesc.Count = 1;
		texd.SampleDesc.Quality = 0;
		texd.Usage = D3D11_USAGE_DEFAULT;
		texd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texd.CPUAccessFlags = 0;
		texd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA srd = {};

		srd.pSysMem = (const void*)data;
		srd.SysMemPitch = m_Width * 4;
		srd.SysMemSlicePitch = 0;

		ID3D11Texture2D* pTexture;
		DX11RenderingApi::GetDevice()->CreateTexture2D(&texd, &srd, &pTexture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
		srvd.Format = texd.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;

		DX11RenderingApi::GetDevice()->CreateShaderResourceView(pTexture, &srvd, &m_Texture);

		stbi_image_free(data);


	}

	DX11Texture::~DX11Texture()
	{
		m_Texture->Release();
	}

	void DX11Texture::Bind(unsigned int slot)
	{
		DX11RenderingApi::GetContext()->PSSetShaderResources(slot, 1, &m_Texture);
	}

	void DX11Texture::Unbind()
	{
		
	}

	unsigned int DX11Texture::GetId()
	{
		return m_Id;
	}

}