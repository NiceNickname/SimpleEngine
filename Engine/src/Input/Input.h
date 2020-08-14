#pragma once
#include <GLFW/glfw3.h>

namespace Engine
{
	class Input
	{
	public:
		static bool IsKeyDown(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float>  MousePosition();
	};
}