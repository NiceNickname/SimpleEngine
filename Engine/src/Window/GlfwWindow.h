#pragma once

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"



namespace Engine
{
	class GlfwWindow : public Window
	{
	public:
		GlfwWindow();
		~GlfwWindow();

		virtual void Update() override;
		virtual bool ShouldClose() override;

		virtual void GetFrameBufferSize(int* width, int* height) override;
		GLFWwindow* GetPointer() { return m_Window; }

	private:
		GLFWwindow* m_Window;

	};
}
