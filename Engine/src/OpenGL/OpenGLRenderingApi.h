#pragma once
#include <Gl/glew.h>
#include "Renderer/RenderingAPI.h"

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