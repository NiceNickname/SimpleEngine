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
		Init();
	}

	GlfwWindow::~GlfwWindow()
	{/*
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();*/

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void GlfwWindow::Init()
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

	void GlfwWindow::Update()
	{
		/* Poll for and process events */
		glfwPollEvents();

		if (Renderer::GetApi() == Renderer::API::DX11)
			DX11RenderingApi::SwapBuffers(1, 0);
		else if (Renderer::GetApi() == Renderer::API::OPENGL)
			glfwSwapBuffers(m_Window);
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