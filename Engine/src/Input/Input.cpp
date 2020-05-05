#include "Input.h"

bool Input::keys[65546];

void Input::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	keys[key] = action != GLFW_RELEASE;
}

bool Input::IsKeyDown(int keycode)
{
	return keys[keycode];
}
