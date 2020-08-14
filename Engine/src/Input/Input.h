#pragma once
#include <GLFW/glfw3.h>

namespace Engine
{
	class Input
	{
	public:
		static void KeyCallBackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ScrollCallBackGLFW(GLFWwindow* window, double xoffset, double yoffset);

		static bool IsKeyDown(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float>  MousePosition();
	};
}