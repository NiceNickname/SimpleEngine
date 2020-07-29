#pragma once
#include "RenderingAPI.h"
#include "OpenGL/OpenGLTexture.h"
#include "glm/glm.hpp"
#include <memory>
struct GLFWwindow;

namespace Engine {

	

	class Renderer
	{
	public:
		enum class API { NONE = 0, OPENGL, DX11 };

		static void Init();
		static void Begin();
		static void End();
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<OpenGLTexture>& texture);
		static void Flush();
		static void ShutDown();
		static void Draw();
		static void SetApi(API api, GLFWwindow* window);

	private:
		static std::unique_ptr<RenderingAPI> m_Api;
	};

}