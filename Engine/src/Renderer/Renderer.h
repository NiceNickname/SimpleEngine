#pragma once
#include "RenderingAPI.h"
#include "Texture.h"
#include "glm/glm.hpp"

struct GLFWwindow;

namespace Engine {

	class Renderer
	{
	public:
		enum class API { NONE = 0, OPENGL, DX11 };

		static void Init();
		static void Begin();
		static void End();
		static void DrawQuad(unsigned int indexcount);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		static void Flush();
		static void ShutDown();
		static void Draw();
		static void SetApi(API api, GLFWwindow* window);
		inline static API GetApi() { return m_ApiName; }
	private:
		static void DrawQuadOpenGL(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuadOpenGL(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		static void DrawQuadDX11(unsigned int indexcount);

	private:
		static std::unique_ptr<RenderingAPI> m_Api;
		static API m_ApiName;
	};

}