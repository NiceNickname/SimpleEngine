#pragma once

#define MAX_TEXTURES 10

#include "Renderer/BatchRenderer.h"

namespace Engine {

	class OpenGLBatchRenderer : public BatchRenderer 
	{
	
	private:

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

			int TextureSlots[MAX_TEXTURES];
			unsigned int TextureSlotIndex = 1;
		};

	public:
		OpenGLBatchRenderer();
		~OpenGLBatchRenderer();

		virtual void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) override;
		virtual void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Draw() override;

	private:
		Data m_Data;
	};

}
