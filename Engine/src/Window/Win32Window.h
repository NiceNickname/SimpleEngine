#pragma once
#include "Window.h"
#include "Windows.h"


namespace Engine {

	class Win32Window : public Window
	{

	public:
		Win32Window(const std::string& name, int width, int height);
		~Win32Window();

		virtual void Update() override;

		virtual bool ShouldClose() override;
		virtual void GetFrameBufferSize(int* width, int* height) override;
		inline HWND& GetHwnd() { return hwnd; }

	private:
		HWND hwnd;
		WNDCLASSEX wc;
		bool shouldClose = false;

	};

}