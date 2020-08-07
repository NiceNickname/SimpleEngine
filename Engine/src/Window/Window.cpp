#include "pch.h"

#include "Window.h"
#include "GlfwWindow.h"
#include "Win32Window.h"

namespace Engine {

	

	Window* Window::Create(Type type)
	{
		if (type == Type::GLFW)
			return new GlfwWindow();
		else if (type == Type::WIN32WINDOW)
			return new Win32Window();
	}


}