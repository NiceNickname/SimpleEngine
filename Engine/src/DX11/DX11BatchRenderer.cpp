#include "pch.h"


#include "DX11BatchRenderer.h"

namespace Engine {

	static const unsigned int MaxTextures = 10;
	static const unsigned int MaxQuadCount = 1000;
	static const unsigned int MaxVertexCount = MaxQuadCount * 4;
	static const unsigned int MaxIndexCount = MaxQuadCount * 6;


	DX11BatchRenderer::DX11BatchRenderer()
	{
		D3DReadFileToBlob(L"../User/res/shaders/VertexShader.cso", &m_Data.VSByteCode);

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

	}

	DX11BatchRenderer::~DX11BatchRenderer()
	{
		m_Data.VertexBuffer->Release();
		m_Data.IndexBuffer->Release();
		m_Data.Layout->Release();
		m_Data.VSByteCode->Release();


		delete[] m_Data.QuadBuffer;
	}

	void DX11BatchRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		m_Data.QuadBufferPtr->Position = { position.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr++;



		m_Data.IndexCount += 6;
	}

	void DX11BatchRenderer::Begin()
	{
		m_Data.QuadBufferPtr = m_Data.QuadBuffer;
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
		m_Data.IndexCount = 0;
	}

}