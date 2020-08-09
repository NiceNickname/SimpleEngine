#include "pch.h"

#include "Input.h"


namespace Engine
{
	bool Input::keys[65546];
	int Input::mouseWheelOffset = 0;


	void Input::KeyCallBackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keys[key] = action != GLFW_RELEASE;
	}

	void Input::KeyDown(int keycode)
	{
		keys[keycode] = true;
	}

	void Input::KeyUp(int keycode)
	{
		keys[keycode] = false;
	}

	bool Input::IsKeyDown(int keycode)
	{
		return keys[keycode];
	}

	void Input::MouseScrolled(int delta)
	{
		mouseWheelOffset = delta;
	}
}
