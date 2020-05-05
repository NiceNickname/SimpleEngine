#pragma once
#include <GLFW/glfw3.h>

class Input
{
private:
	static bool keys[];

public:
	static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool IsKeyDown(int keycode);
};