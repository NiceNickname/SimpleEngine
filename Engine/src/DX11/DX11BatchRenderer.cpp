#include "pch.h"
#include "DX11BatchRenderer.h"

#define VERTEX_SHADER_PATH L"../User/res/shaders/VertexShader.cso"

namespace Engine {

	static const unsigned int MaxTextures = 32;
	static const unsigned int MaxQuadCount = 10;
	static const unsigned int MaxVertexCount = MaxQuadCount * 4;
	static const unsigned int MaxIndexCount = MaxQuadCount * 6;


	DX11BatchRenderer::DX11BatchRenderer()
	{
		m_Stats.QuadPerDrawCall = MaxQuadCount;

		D3DReadFileToBlob(VERTEX_SHADER_PATH, &m_Data.VSByteCode);

		m_Data.QuadBuffer = new Vertex[MaxVertexCount];

		// vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(Vertex) * MaxVertexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &m_Data.VertexBuffer);


		//layout

		D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORDS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXINDEX", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};



		DX11RenderingApi::GetDevice()->CreateInputLayout(ied, sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC),
			m_Data.VSByteCode->GetBufferPointer(), m_Data.VSByteCode->GetBufferSize(), &m_Data.Layout);

		DX11RenderingApi::GetContext()->IASetInputLayout(m_Data.Layout);

		UINT stride = (UINT)sizeof(Vertex);
		UINT offset = 0;
		DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &m_Data.VertexBuffer, &stride, &offset);

		unsigned int indices[MaxIndexCount];
		unsigned int IndexOffset = 0;

		for (int i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + IndexOffset;
			indices[i + 1] = 1 + IndexOffset;
			indices[i + 2] = 2 + IndexOffset;

			indices[i + 3] = 2 + IndexOffset;
			indices[i + 4] = 3 + IndexOffset;
			indices[i + 5] = 0 + IndexOffset;

			IndexOffset += 4;
		}

		// index buffer


		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(indices);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &m_Data.IndexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		DX11RenderingApi::GetContext()->Map(m_Data.IndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, indices, sizeof(indices));
		DX11RenderingApi::GetContext()->Unmap(m_Data.IndexBuffer, NULL);

		DX11RenderingApi::GetContext()->IASetIndexBuffer(m_Data.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		D3D11_TEXTURE2D_DESC texd = {};
		texd.Width = 1;
		texd.Height = 1;
		texd.MipLevels = 1;
		texd.ArraySize = 1;
		texd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		texd.SampleDesc.Count = 1;
		texd.SampleDesc.Quality = 0;
		texd.Usage = D3D11_USAGE_DEFAULT;
		texd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texd.CPUAccessFlags = 0;
		texd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA srd = {};

		unsigned int color = 0xffffffff;

		srd.pSysMem = &color;
		srd.SysMemPitch = sizeof(color);

		ID3D11Texture2D* pTexture;
		DX11RenderingApi::GetDevice()->CreateTexture2D(&texd, &srd, &pTexture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
		srvd.Format = texd.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;

		DX11RenderingApi::GetDevice()->CreateShaderResourceView(pTexture, &srvd, &m_Data.WhiteTexture);
		DX11RenderingApi::GetContext()->PSSetShaderResources(0, 1, &m_Data.WhiteTexture);

	}

	DX11BatchRenderer::~DX11BatchRenderer()
	{
		m_Data.VertexBuffer->Release();
		m_Data.IndexBuffer->Release();
		m_Data.Layout->Release();
		m_Data.VSByteCode->Release();
		m_Data.WhiteTexture->Release();


		delete[] m_Data.QuadBuffer;
	}

	void DX11BatchRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (m_Data.IndexCount >= MaxIndexCount)
		{
			End();
			Draw();
			unsigned int tmpdrawcalls = m_Stats.DrawCallsCount;
			unsigned int tmpQuadCount = m_Stats.QuadsCount;
			Begin();
			m_Stats.DrawCallsCount = tmpdrawcalls;
			m_Stats.QuadsCount = tmpQuadCount;
		}

		float TextureIndex = 0.0f;

		m_Data.QuadBufferPtr->Position = { position.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.IndexCount += 6;
	}

	void DX11BatchRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		if (m_Data.IndexCount >= MaxIndexCount || m_Data.TextureSlotIndex > MaxTextures - 1)
		{
			End();
			Draw();
			unsigned int tmpdrawcalls = m_Stats.DrawCallsCount;
			unsigned int tmpQuadCount = m_Stats.QuadsCount;
			Begin();
			m_Stats.DrawCallsCount = tmpdrawcalls;
			m_Stats.QuadsCount = tmpQuadCount;
		}

		const glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float TextureIndex = 0.0f;

		for (int i = 0; i < m_Data.TextureSlotIndex; i++)
		{
			if (m_Data.TextureSlots[i] == texture->GetId())
				TextureIndex = float(i);
		}

		if (TextureIndex == 0.0f)
		{
			TextureIndex = (float)m_Data.TextureSlotIndex;
			m_Data.TextureSlots[m_Data.TextureSlotIndex] = texture->GetId();
			m_Data.TextureSlotIndex++;
		}

		m_Data.QuadBufferPtr->Position = { position.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.IndexCount += 6;
	}

	void DX11BatchRenderer::Begin()
	{
		m_Data.QuadBufferPtr = m_Data.QuadBuffer;
		m_Stats.DrawCallsCount = 0;
		m_Stats.QuadsCount = 0;
	}

	void DX11BatchRenderer::End()
	{
		unsigned int size = (uint8_t*)m_Data.QuadBufferPtr - (uint8_t*)m_Data.QuadBuffer;
		// bind vertexbuffer
		D3D11_MAPPED_SUBRESOURCE ms;
		DX11RenderingApi::GetContext()->Map(m_Data.VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, m_Data.QuadBuffer, size);
		DX11RenderingApi::GetContext()->Unmap(m_Data.VertexBuffer, NULL);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &m_Data.VertexBuffer, &stride, &offset);

		// bind layout
		DX11RenderingApi::GetContext()->IASetInputLayout(m_Data.Layout);

		// bind indexbuffer
		DX11RenderingApi::GetContext()->IASetIndexBuffer(m_Data.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void DX11BatchRenderer::Draw()
	{
		DX11RenderingApi::GetContext()->DrawIndexed(m_Data.IndexCount, 0, 0);
		m_Stats.DrawCallsCount++;
		m_Stats.QuadsCount += m_Data.IndexCount / 6;
		m_Data.IndexCount = 0;
	}

}