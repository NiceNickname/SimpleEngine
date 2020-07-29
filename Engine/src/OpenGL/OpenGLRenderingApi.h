#pragma once
#include "Renderer/RenderingAPI.h"
#include <Gl/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	class OpenGLRenderingApi : public RenderingAPI
	{
	public:
		OpenGLRenderingApi(GLFWwindow* window);
		~OpenGLRenderingApi();
		virtual void Init(GLFWwindow* window) override;
		virtual void ShutDown() override;
	};
}