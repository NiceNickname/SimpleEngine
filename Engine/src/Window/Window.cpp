#include "pch.h"

#include "Window.h"
#include "Input/Input.h"
#include <iostream>


#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Engine
{
	Window::Window()
	{
		Init();
	}

	Window::~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Init()
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

		if (glewInit() != GLEW_OK)
			std::cout << "glew not initialized" << std::endl;

		glEnable(GL_DEPTH_TEST);
		
		glfwSetKeyCallback(m_Window, Input::KeyCallBack);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapInterval(1);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void Window::Update()
	{
		/* Poll for and process events */
		glfwPollEvents();

		glfwSwapBuffers(m_Window);
	}
}