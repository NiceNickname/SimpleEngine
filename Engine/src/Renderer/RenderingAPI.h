#pragma once

struct GLFWwindow;

namespace Engine {
	class RenderingAPI
	{
	public:
		virtual void Init(GLFWwindow* window) = 0;
		virtual void ShutDown() = 0;
	};
}