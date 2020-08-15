#pragma once


namespace Engine
{
	class Input
	{
	public:
		static bool IsKeyDown(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float>  MousePosition();


	private:
		static bool IsKeyDownWin32(int keycode);
		static bool IsMouseButtonPressedWin32(int button);
		static std::pair<float, float> MousePositionWin32();


		static bool IsKeyDownGlfw(int keycode);
		static bool IsMouseButtonPressedGlfw(int button);
		static std::pair<float, float> MousePostionGlfw();
	};
}