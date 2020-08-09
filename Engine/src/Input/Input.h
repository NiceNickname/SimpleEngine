#pragma once
#include <GLFW/glfw3.h>

namespace Engine
{
	class Input
	{
	private:
		static bool keys[];
		static int mouseWheelOffset;
	public:
		static void KeyCallBackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void KeyDown(int keycode);
		static void KeyUp(int keycode);
		static bool IsKeyDown(int keycode);

		static void MouseScrolled(int delta);
		static int GetMouseWheelOffset() { return mouseWheelOffset; }
	};
}