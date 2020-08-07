#include "pch.h"

#include "GlfwWindow.h"
#include "Input/Input.h"
#include <iostream>


#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "Renderer/Renderer.h"
#include "DX11/DX11RenderingApi.h"

namespace Engine
{
	GlfwWindow::GlfwWindow()
	{
		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(1280, 720, "Engine", NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return;
		}


		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		glfwSwapInterval(1);

		glfwSetKeyCallback(m_Window, Input::KeyCallBack);
	}

	GlfwWindow::~GlfwWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void GlfwWindow::Update()
	{
		/* Poll for and process events */
		glfwPollEvents();

	}

	bool GlfwWindow::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void GlfwWindow::GetFrameBufferSize(int* width, int* height)
	{
		glfwGetFramebufferSize(m_Window, width, height);
	}

}