#pragma once
#include <Gl/glew.h>


#include "GLFW/glfw3.h"

#include "Renderer/RenderingAPI.h"
#include "glm/glm.hpp"

namespace Engine
{
	class OpenGLRenderingApi : public RenderingAPI
	{
	public:
		OpenGLRenderingApi(const std::unique_ptr<Window>& window);
		~OpenGLRenderingApi();

		virtual void ShutDown() override;
		virtual void SwapBuffers() override;
		virtual void ClearBuffer() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetVSync(bool enabled) override;


	private:
		GLFWwindow* m_Window;
	};
}