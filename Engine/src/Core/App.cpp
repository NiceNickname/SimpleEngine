#include "pch.h"

#include "App.h"
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#include "Renderer/Renderer.h"
#include "DX11/DX11RenderingApi.h"

namespace Engine
{
	void App::Run()
	{
		Start();

		while (m_Running)
		{
			Update();

			if (Renderer::GetApi() == Renderer::API::OPENGL)
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			else if (Renderer::GetApi() == Renderer::API::DX11)
				DX11RenderingApi::ClearBuffer();
			
			
			Renderer::Prepare();

			Render();
			
			ImGuiBegin();
			ImGuiRender();
			ImGuiEnd();
			

			m_Window->Update();
			Renderer::SwapBuffers();

			if (m_Window->ShouldClose())
				m_Running = false;
		}
	}

	void App::ImGuiBegin()
	{
		// Start the Dear ImGui frame
		if (m_Api == Renderer::API::OPENGL)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		else if (m_Api == Renderer::API::DX11)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
		}
		
	}

	void App::ImGuiEnd()
	{
		ImGuiIO& io = ImGui::GetIO();

		if (m_Api == Renderer::API::OPENGL)
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
		else if (m_Api == Renderer::API::DX11)
		{
			// Rendering
			ImGui::Render();
			/*ID3D11RenderTargetView* backbuffer = DX11RenderingApi::GetBackBuffer();
			DX11RenderingApi::GetContext()->OMSetRenderTargets(1, &backbuffer, NULL);
			float color[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			DX11RenderingApi::GetContext()->ClearRenderTargetView(backbuffer, (float*)&color);*/
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			// Update and Render additional Platform Windows
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}

		}
		
	}
}
