#include "pch.h"
#include "Window/GlfwWindow.h"
#include "Renderer.h"

#include "OpenGL/OpenGLIndexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/OpenGLRenderingApi.h"
#include "DX11/DX11Shader.h"

namespace Engine {

	std::unique_ptr<RenderingAPI> Renderer::m_Api;
	Renderer::API Renderer::m_ApiName = Renderer::API::NONE;


	static const unsigned int MaxTextures = 10;
	static const unsigned int MaxQuadCount = 1000;
	static const unsigned int MaxVertexCount = MaxQuadCount * 4;
	static const unsigned int MaxIndexCount = MaxQuadCount * 6;


	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexIndex;
	};

	struct VertexDX11
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	struct DataDX11
	{
		ID3D11Buffer* VertexBuffer;
		ID3D11Buffer* IndexBuffer;
		ID3D11InputLayout* Layout;

		ID3DBlob* VSByteCode;

		unsigned int IndexCount = 0;

		VertexDX11* QuadBuffer = nullptr;
		VertexDX11* QuadBufferPtr = nullptr;
	};

	struct Data
	{
		unsigned int QuadVA = 0;
		unsigned int QuadVB = 0;
		unsigned int QuadIB = 0;

		unsigned int WhiteTexture = 0;
		unsigned int WhiteTextureSlot = 0;

		unsigned int IndexCount = 0;

		Vertex* QuadBuffer = nullptr;
		Vertex* QuadBufferPtr = nullptr;

		int TextureSlots[MaxTextures];
		unsigned int TextureSlotIndex = 1;
	};

	static Data s_Data;
	static DataDX11 s_DataDX11;


	void Renderer::Init()
	{

		if (m_ApiName == Renderer::API::OPENGL)
		{
			s_Data.QuadBuffer = new Vertex[MaxVertexCount];

			glGenVertexArrays(1, &s_Data.QuadVA);
			glBindVertexArray(s_Data.QuadVA);

			glGenBuffers(1, &s_Data.QuadVB);
			glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexIndex));
		}
		else if (m_ApiName == Renderer::API::DX11)
		{
			s_DataDX11.QuadBuffer = new VertexDX11[MaxVertexCount];

			

			

			// vertex buffer
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));

			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VertexDX11) * MaxVertexCount;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &s_DataDX11.VertexBuffer);

			
			//layout
		
			D3D11_INPUT_ELEMENT_DESC ied[] = {
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};
			


			DX11RenderingApi::GetDevice()->CreateInputLayout(ied, sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC),
				s_DataDX11.VSByteCode->GetBufferPointer(), s_DataDX11.VSByteCode->GetBufferSize(), &s_DataDX11.Layout);

			DX11RenderingApi::GetContext()->IASetInputLayout(s_DataDX11.Layout);

			UINT stride = (UINT)sizeof(VertexDX11);
			UINT offset = 0;
			DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &s_DataDX11.VertexBuffer, &stride, &offset);
			
			
		}



		unsigned int indices[MaxIndexCount];
		unsigned int offset = 0;

		for (int i = 0; i < MaxIndexCount; i+=6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		if (m_ApiName == Renderer::API::OPENGL)
		{
			glGenBuffers(1, &s_Data.QuadIB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


			// white texture

			glGenTextures(1, &s_Data.WhiteTexture);
			glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			unsigned int color = 0xffffffff;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
			s_Data.TextureSlots[0] = s_Data.WhiteTexture;

			for (int i = 1; i < MaxTextures; i++)
				s_Data.TextureSlots[i] = 0;
		}
		else if (m_ApiName == Renderer::API::DX11)
		{
			// index buffer

			D3D11_BUFFER_DESC bd;

			ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(indices);
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			DX11RenderingApi::GetDevice()->CreateBuffer(&bd, NULL, &s_DataDX11.IndexBuffer);

			D3D11_MAPPED_SUBRESOURCE ms;
			DX11RenderingApi::GetContext()->Map(s_DataDX11.IndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, indices, sizeof(indices));
			DX11RenderingApi::GetContext()->Unmap(s_DataDX11.IndexBuffer, NULL);

			DX11RenderingApi::GetContext()->IASetIndexBuffer(s_DataDX11.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		}


	}

	void Renderer::ShutDown()
	{
		if (m_Api.get() != nullptr)
			m_Api.reset();

		if (m_ApiName == API::OPENGL)
		{
			glDeleteBuffers(1, &s_Data.QuadVB);
			glDeleteBuffers(1, &s_Data.QuadIB);
			glDeleteVertexArrays(1, &s_Data.QuadVA);

			glDeleteTextures(1, &s_Data.WhiteTexture);

		}

		if (s_Data.QuadBuffer != nullptr)
			delete[] s_Data.QuadBuffer;
		if (s_DataDX11.QuadBuffer != nullptr)
			delete[] s_DataDX11.QuadBuffer;
	}

	void Renderer::SwapBuffers()
	{
		m_Api->SwapBuffers();
	}

	void Renderer::ClearBuffer()
	{
		m_Api->ClearBuffer();
	}

	void Renderer::Begin()
	{
		s_Data.QuadBufferPtr = s_Data.QuadBuffer;
		s_DataDX11.QuadBufferPtr = s_DataDX11.QuadBuffer;
	}

	void Renderer::End()
	{

		if (m_ApiName == Renderer::API::OPENGL)
		{
			unsigned int size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
			glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer);
		}
		else if (m_ApiName == Renderer::API::DX11)
		{
			unsigned int size = (uint8_t*)s_DataDX11.QuadBufferPtr - (uint8_t*)s_DataDX11.QuadBuffer;
			// bind vertexbuffer
			D3D11_MAPPED_SUBRESOURCE ms;
			DX11RenderingApi::GetContext()->Map(s_DataDX11.VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, s_DataDX11.QuadBuffer, size);
			DX11RenderingApi::GetContext()->Unmap(s_DataDX11.VertexBuffer, NULL);

			UINT stride = sizeof(VertexDX11);
			UINT offset = 0;
			DX11RenderingApi::GetContext()->IASetVertexBuffers(0, 1, &s_DataDX11.VertexBuffer, &stride, &offset);

			// bind layout
			DX11RenderingApi::GetContext()->IASetInputLayout(s_DataDX11.Layout);

			// bind indexbuffer
			DX11RenderingApi::GetContext()->IASetIndexBuffer(s_DataDX11.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		}
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (m_ApiName == API::NONE)
			std::cout << "None rendering API is set\n";
		else if (m_ApiName == API::OPENGL)
			DrawQuadOpenGL(position, size, color);
		else if (m_ApiName == API::DX11)
			DrawQuadDX11(position, size, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		if (m_ApiName == API::NONE)
			std::cout << "None rendering API is set\n";
		else if (m_ApiName == API::OPENGL)
			DrawQuadOpenGL(position, size, texture);
		else if (m_ApiName == API::DX11)
			std::cout << "DX11 currently is not supported\n";
	}


	void Renderer::DrawQuad()
	{
		DrawQuadDX11();
	}

	void Renderer::Flush()
	{
		// TODO: drawcall
	}

	void Renderer::Draw()
	{

		if (m_ApiName == Renderer::API::OPENGL)
		{
			for (unsigned int i = 0; i < MaxTextures; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, s_Data.TextureSlots[i]);
			}

			glBindVertexArray(s_Data.QuadVA);
			glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);

			s_Data.IndexCount = 0;
			s_Data.TextureSlotIndex = 1;
		}
		else if (m_ApiName == Renderer::API::DX11)
		{
			DX11RenderingApi::GetContext()->DrawIndexed(s_DataDX11.IndexCount, 0, 0);
			s_DataDX11.IndexCount = 0;
		}

	}

	void Renderer::SetApi(API api, std::unique_ptr<Window>& window)
	{
		m_ApiName = api;
		if (api == API::NONE)
			std::cout << "Cannot set API to NONE\n";
		else if (api == API::OPENGL)
		{
			if (m_Api.get() != nullptr)
				m_Api.reset();
			window.reset(Window::Create("Engine", 1280, 720, Window::Type::GLFW));
			m_Api.reset(RenderingAPI::Create(window));
		}
		else if (api == API::DX11)
		{
			if (m_Api.get() != nullptr)
				m_Api.reset();
			window.reset(Window::Create("Engine", 1280, 720, Window::Type::WIN32WINDOW));
			m_Api.reset(RenderingAPI::Create(window));
		}
	}

	void Renderer::SetVSByteCode(ID3DBlob* VShaderByteCode)
	{
		s_DataDX11.VSByteCode = VShaderByteCode;
	}

	void Renderer::Prepare()
	{
		m_Api->Prepare();
	}

	void Renderer::DrawQuadOpenGL(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		if (s_Data.IndexCount >= MaxIndexCount || s_Data.TextureSlotIndex > 9)
		{
			End();
			Draw();
			Begin();
		}

		const glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float TextureIndex = 0.0f;

		for (int i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.TextureSlots[i] == texture->GetId())
				TextureIndex = float(i);
		}

		if (TextureIndex == 0.0f)
		{
			TextureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture->GetId();
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadBufferPtr->Position = { position.x, position.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.IndexCount += 6;
	}

	void Renderer::DrawQuadOpenGL(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (s_Data.IndexCount >= MaxIndexCount)
		{
			End();
			Draw();
			Begin();
		}

		float TextureIndex = 0.0f;

		s_Data.QuadBufferPtr->Position = { position.x, position.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data.QuadBufferPtr->TexIndex = TextureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.IndexCount += 6;
	}

	void Renderer::DrawQuadDX11()
	{
		DX11RenderingApi::GetContext()->DrawIndexed(6, 0, 0);	
	}

	void Renderer::DrawQuadDX11(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_DataDX11.QuadBufferPtr->Position = { position.x, position.y, position.z };
		s_DataDX11.QuadBufferPtr->Color = color;
		s_DataDX11.QuadBufferPtr++;
			  
		s_DataDX11.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_DataDX11.QuadBufferPtr->Color = color;
		s_DataDX11.QuadBufferPtr++;

		s_DataDX11.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_DataDX11.QuadBufferPtr->Color = color;
		s_DataDX11.QuadBufferPtr++;

		s_DataDX11.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_DataDX11.QuadBufferPtr->Color = color;
		s_DataDX11.QuadBufferPtr++;
			  
			  
			  
		s_DataDX11.IndexCount += 6;
	}

}
