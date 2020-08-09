#pragma once
#include "OpenGL/OpenGLRenderingApi.h"
#include "DX11/DX11RenderingApi.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "Window/Window.h"

namespace Engine {

	// TODO: refactor DrawQuadDX11 function
	// implement Flush function

	class Renderer
	{
	public:
		enum class API { NONE = 0, OPENGL, DX11 };

		static void Init();
		static void Begin();
		static void End();
		static void DrawQuad();
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		static void Flush();
		static void ShutDown();
		static void SwapBuffers();
		static void ClearBuffer();
		static void Draw();
		static void SetApi(API api, std::unique_ptr<Window>& window);
		
		// this function is for additional operations before actual rendering each frame (e.g. setting render target for dx11)
		static void Prepare();

		inline static API GetApi() { return m_ApiName; }
	private:
		//OPENGL functions
		static void DrawQuadOpenGL(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuadOpenGL(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		
		// DIRECTX11 functions
		static void DrawQuadDX11();
		static void DrawQuadDX11(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

	private:
		static std::unique_ptr<RenderingAPI> m_Api;
		static API m_ApiName;
	};

}