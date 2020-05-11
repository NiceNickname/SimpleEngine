#include "pch.h"

#include "App.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Engine
{
	void App::Run()
	{
		Start();

		while (m_Running)
		{
			Update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			Render();
			ImGuiBegin();
			ImGuiRender();
			ImGuiEnd();

			m_Window->Update();

			if (glfwWindowShouldClose(m_Window->GetPointer()))
				m_Running = false;
		}
	}

	void App::ImGuiBegin()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void App::ImGuiEnd()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window->GetPointer(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}
