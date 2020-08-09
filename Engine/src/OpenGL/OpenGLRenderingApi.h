#pragma once
#include <Gl/glew.h>


#include "GLFW/glfw3.h"

#include "Renderer/RenderingAPI.h"

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

	private:
		GLFWwindow* m_Window;
	};
}