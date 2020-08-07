#include "pch.h"
#include "OpenGLRenderingApi.h"
#include "Window/GlfwWindow.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Engine {

	OpenGLRenderingApi::OpenGLRenderingApi(const std::unique_ptr<Window>& window)
	{
		if (glewInit() != GLEW_OK)
			std::cout << "glew not initialized" << std::endl;

		glEnable(GL_DEPTH_TEST);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



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

		m_Window = static_cast<GlfwWindow*>(window.get())->GetPointer();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	OpenGLRenderingApi::~OpenGLRenderingApi()
	{
		ShutDown();
	}

	void OpenGLRenderingApi::ShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void OpenGLRenderingApi::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

}