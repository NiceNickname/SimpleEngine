#include "pch.h"

#include "GlfwWindow.h"
#include "Input/Input.h"


#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "Renderer/Renderer2D.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"

namespace Engine
{
	GlfwWindow::GlfwWindow(const std::string& name, int width, int height)
	{
		m_Name = name;
		m_Width = width;
		m_Height = height;

		

		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return;
		}


		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		glfwSwapInterval(1);


		glfwSetWindowUserPointer(m_Window, &m_Callback);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			auto& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowResizedEvent event(width, height);
			callback(event);
			
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				callback(event);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				callback(event);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				callback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
		{
			auto& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			
			KeyTypedEvent event(codepoint);
			callback(event);

		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			auto& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			callback(event);
			
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			auto& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x, (float)y);
			callback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						callback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						callback(event);
						break;
					}
			}
		});
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