#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Window.h"



namespace Engine
{
	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(const std::string& name, int width, int height);
		~GlfwWindow();

		virtual void Update() override;
		virtual bool ShouldClose() override;

		virtual void GetFrameBufferSize(int* width, int* height) override;
		GLFWwindow* GetPointer() { return m_Window; }

	private:
		GLFWwindow* m_Window;
		

	};
}
