#include "pch.h"

#include "App.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#include "Renderer/Renderer2D.h"
#include "Window/GlfwWindow.h"

namespace Engine
{
	void App::Run()
	{
		ChooseApi();

		// window creation and chosen API initialization
		Renderer2D::SetApi(m_Api, m_Window);


		Start();

		while (m_Running)
		{
			Update();

			Renderer2D::ClearBuffer();
			
			// this function is for additional operations before actual rendering each frame (e.g. setting render target for dx11)
			Renderer2D::Prepare();

			Render();
			
			ImGuiBegin();
			ImGuiRender();
			ImGuiEnd();
			

			m_Window->Update();
			Renderer2D::SwapBuffers();

			if (m_Window->ShouldClose())
				m_Running = false;
		}

		ShutDown();
	}

	void App::ImGuiBegin()
	{
		// Start the Dear ImGui frame
		if (m_Api == Renderer2D::API::OPENGL)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		else if (m_Api == Renderer2D::API::DX11)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
		}
		
	}

	void App::ImGuiEnd()
	{
		ImGuiIO& io = ImGui::GetIO();

		if (m_Api == Renderer2D::API::OPENGL)
		{
			// Rendering
			ImGui::Render();
			int display_w = 0, display_h = 0;
			m_Window->GetFrameBufferSize(&display_w, &display_h);
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
		else if (m_Api == Renderer2D::API::DX11)
		{
			// Rendering
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			// Update and Render additional Platform Windows
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}

		}
		
	}

	void App::ShutDown()
	{
		Renderer2D::ShutDown();
	}

}
