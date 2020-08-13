#pragma once
#include "Texture.h"
#include "glm/glm.hpp"
#include "Window/Window.h"
#include "RenderingAPI.h"
#include "BatchRenderer.h"

namespace Engine {

	class Renderer2D
	{
	public:
		enum class API { NONE = 0, OPENGL, DX11 };

		static void Init();
		static void Begin();
		static void End();
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		static BatchRenderer::stats GetStats() { return m_BatchRenderer->GetStats(); }
		static void Draw();
		static void ShutDown();
		static void SwapBuffers();
		static void ClearBuffer();
		static void SetApi(API api, std::unique_ptr<Window>& window);
		
		// this function is for additional operations before actual rendering each frame (e.g. setting render target for dx11)
		static void Prepare();

		inline static API GetApi() { return m_ApiName; }

	private:
		static std::unique_ptr<RenderingAPI> m_Api;
		static std::unique_ptr<BatchRenderer> m_BatchRenderer;
		static API m_ApiName;
	};

}