#include "pch.h"

#include "Renderer.h"

#include "OpenGL/OpenGLIndexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/OpenGLRenderingApi.h"

namespace Engine {

	std::unique_ptr<RenderingAPI> Renderer::m_Api;

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


	void Renderer::Init()
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

	void Renderer::ShutDown()
	{
		glDeleteBuffers(1, &s_Data.QuadVB);
		glDeleteBuffers(1, &s_Data.QuadIB);
		glDeleteVertexArrays(1, &s_Data.QuadVA);

		glDeleteTextures(1, &s_Data.WhiteTexture);

		delete[] s_Data.QuadBuffer;
	}

	void Renderer::Begin()
	{
		s_Data.QuadBufferPtr = s_Data.QuadBuffer;
	}

	void Renderer::End()
	{
		GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer);
	}

	void Renderer::Draw()
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

	void Renderer::SetApi(API api, GLFWwindow* window)
	{
		if (api == API::NONE)
			std::cout << "Cannot set API to NONE\n";
		else if (api == API::OPENGL)
		{
			if (m_Api.get() != nullptr)
				m_Api->ShutDown();
			m_Api = std::make_unique<OpenGLRenderingApi>(window);
		}
		else if (api == API::DX11)
			std::cout << "DX11 currently is not supported\n";
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<OpenGLTexture>& texture)
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

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
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

}