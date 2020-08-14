#include "pch.h"

#include "Input.h"

#if 0
namespace Engine
{
	bool Input::keys[65546];
	float Input::mouseWheelOffset = 0.0f;


	void Input::KeyCallBackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keys[key] = action != GLFW_RELEASE;
	}

	void Input::ScrollCallBackGLFW(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouseWheelOffset = yoffset * 0.25f;
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
		mouseWheelOffset = (float)delta * 0.001f;
	}
}
#endif