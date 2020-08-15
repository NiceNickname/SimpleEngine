#include "pch.h"

#include "Input.h"
#include "Renderer/Renderer2D.h"

namespace Engine {




	bool Input::IsKeyDown(int keycode)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return IsKeyDownWin32(keycode);
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return IsKeyDownGlfw(keycode);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return IsMouseButtonPressedWin32(button);
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return IsMouseButtonPressedGlfw(button);
	}

	std::pair<float, float> Input::MousePosition()
	{
		if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return MousePositionWin32();
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return MousePositionWin32();
	}


}