#include "pch.h"

#include "Core/App.h"
#include "Window/GlfwWindow.h"
#include "Input.h"


namespace Engine {


	bool Input::IsKeyDown(int keycode)
	{
		auto& window = static_cast<GlfwWindow&>(*(App::Get()->GetWindow().get()));
		auto state = glfwGetKey(static_cast<GLFWwindow*>(window.GetPointer()), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto& window = static_cast<GlfwWindow&>(*(App::Get()->GetWindow().get()));

		auto state = glfwGetMouseButton(window.GetPointer(), button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::MousePosition()
	{
		auto& window = static_cast<GlfwWindow&>(*(App::Get()->GetWindow().get()));

		double x, y;
		glfwGetCursorPos(window.GetPointer(), &x, &y);

		return std::make_pair((float)x, (float)y);
	}

	
}