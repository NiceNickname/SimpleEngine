#include "pch.h"

#include "Window.h"
#include "GlfwWindow.h"

namespace Engine {

	

	Window* Window::Create(WindowType type)
	{
		if (type == WindowType::GLFW)
			return new GlfwWindow();
	}


}