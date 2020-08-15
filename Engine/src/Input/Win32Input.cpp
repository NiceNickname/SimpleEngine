#include "pch.h"


#include "Input.h"
#include <Windows.h>

namespace Engine {

	bool Input::IsKeyDownWin32(int keycode)
	{
		SHORT result = GetKeyState(keycode);
		return result & 0x8000;
	}

	bool Input::IsMouseButtonPressedWin32(int button)
	{
		return GetKeyState(button) & 0x8000;
	}

	std::pair<float, float>  Input::MousePositionWin32()
	{
		LPPOINT pos;
		GetCursorPos(pos);
		return std::make_pair(pos->x, pos->y);
	}

}