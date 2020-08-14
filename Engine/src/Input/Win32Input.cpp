#include "pch.h"
#include "Input.h"
#include <Windows.h>

namespace Engine {

	bool Input::IsKeyDown(int keycode)
	{
		return GetKeyState(keycode) & 0x80;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return GetKeyState(button) & 0x80;
	}

	std::pair<float, float>  Input::MousePosition()
	{
		LPPOINT pos;
		GetCursorPos(pos);
		return std::make_pair(pos->x, pos->y);
	}

}