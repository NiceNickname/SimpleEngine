#pragma once

#include "DX11RenderingApi.h"
#include "Renderer/BatchRenderer.h"

namespace Engine {

	class DX11BatchRenderer : public BatchRenderer
	{

	private:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
		};

		struct Data
		{
			ID3D11Buffer* VertexBuffer;
			ID3D11Buffer* IndexBuffer;
			ID3D11InputLayout* Layout;

			ID3DBlob* VSByteCode;

			unsigned int IndexCount = 0;

			Vertex* QuadBuffer = nullptr;
			Vertex* QuadBufferPtr = nullptr;
		};
	public:
		DX11BatchRenderer();
		~DX11BatchRenderer();

		virtual void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Draw() override;

		
	private:
		Data m_Data;
	};

}
