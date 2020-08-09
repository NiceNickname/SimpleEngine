#include "pch.h"

#include "Window.h"
#include "GlfwWindow.h"
#include "Win32Window.h"

namespace Engine {

	

	Window* Window::Create(const std::string& name, int width, int height, Type type)
	{
		if (type == Type::GLFW)
			return new GlfwWindow(name, width, height);
		else if (type == Type::WIN32WINDOW)
			return new Win32Window(name, width, height);
	}


}