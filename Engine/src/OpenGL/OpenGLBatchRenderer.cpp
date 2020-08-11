#include "pch.h"

#include "OpenGLBatchRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine {

	static const unsigned int MaxTextures = 10;
	static const unsigned int MaxQuadCount = 1000;
	static const unsigned int MaxVertexCount = MaxQuadCount * 4;
	static const unsigned int MaxIndexCount = MaxQuadCount * 6;

	OpenGLBatchRenderer::OpenGLBatchRenderer()
	{
		m_Data.QuadBuffer = new Vertex[MaxVertexCount];

		glGenVertexArrays(1, &m_Data.QuadVA);
		glBindVertexArray(m_Data.QuadVA);

		glGenBuffers(1, &m_Data.QuadVB);
		glBindBuffer(GL_ARRAY_BUFFER, m_Data.QuadVB);
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

		for (int i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

			glGenBuffers(1, &m_Data.QuadIB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Data.QuadIB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


			// white texture

			glGenTextures(1, &m_Data.WhiteTexture);
			glBindTexture(GL_TEXTURE_2D, m_Data.WhiteTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			unsigned int color = 0xffffffff;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
			m_Data.TextureSlots[0] = m_Data.WhiteTexture;

			for (int i = 1; i < MaxTextures; i++)
				m_Data.TextureSlots[i] = 0;

			glBindVertexArray(0);

	}

	OpenGLBatchRenderer::~OpenGLBatchRenderer()
	{
		glDeleteBuffers(1, &m_Data.QuadVB);
		glDeleteBuffers(1, &m_Data.QuadIB);
		glDeleteVertexArrays(1, &m_Data.QuadVA);

		glDeleteTextures(1, &m_Data.WhiteTexture);

		delete[] m_Data.QuadBuffer;
	}

	void OpenGLBatchRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (m_Data.IndexCount >= MaxIndexCount)
		{
			End();
			Draw();
			Begin();
		}

		float TextureIndex = 0.0f;

		m_Data.QuadBufferPtr->Position = { position.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.IndexCount += 6;
	}

	void OpenGLBatchRenderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		if (m_Data.IndexCount >= MaxIndexCount || m_Data.TextureSlotIndex > 9)
		{
			End();
			Draw();
			Begin();
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

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.QuadBufferPtr->Position = { position.x, position.y + size.y, position.z };
		m_Data.QuadBufferPtr->Color = color;
		m_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		m_Data.QuadBufferPtr->TexIndex = TextureIndex;
		m_Data.QuadBufferPtr++;

		m_Data.IndexCount += 6;
	}

	void OpenGLBatchRenderer::Begin()
	{
		m_Data.QuadBufferPtr = m_Data.QuadBuffer;
	}

	void OpenGLBatchRenderer::End()
	{
		unsigned int size = (uint8_t*)m_Data.QuadBufferPtr - (uint8_t*)m_Data.QuadBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, m_Data.QuadVB);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_Data.QuadBuffer);
	}

	void OpenGLBatchRenderer::Draw()
	{
		for (unsigned int i = 0; i < MaxTextures; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_Data.TextureSlots[i]);
		}

		glBindVertexArray(m_Data.QuadVA);
		glDrawElements(GL_TRIANGLES, m_Data.IndexCount, GL_UNSIGNED_INT, nullptr);

		m_Data.IndexCount = 0;
		m_Data.TextureSlotIndex = 1;
	}

}