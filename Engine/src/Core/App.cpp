#include "pch.h"

#include "App.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx11.h"

#include "Renderer/Renderer2D.h"
#include "Window/GlfwWindow.h"
#include <functional>

#define BIND_EVENT_FN(fn) std::bind(&App::##fn, this, std::placeholders::_1)

namespace Engine
{
	App* App::s_Instance = nullptr;

	void App::Run()
	{
		ChooseApi();

		// window creation and chosen API initialization
		Renderer2D::SetApi(m_Api, m_Window, BIND_EVENT_FN(OnEvent));

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

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		
		// application events handling
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));

		// keyboard events handling
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(OnKeyTyped));

		// mouse events handling
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolled));

	}


	void App::OnWindowClose(WindowClosedEvent& e)
	{
		m_Running = false;
	}

	void App::OnWindowResize(WindowResizedEvent& e)
	{
		m_Window->SetWidth(e.m_Width);
		m_Window->SetHeight(e.m_Height);
	}

}
