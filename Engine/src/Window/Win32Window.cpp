#include "pch.h"

#include <Windows.h>
#include "Win32Window.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"

#include "Input/Input.h"

	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Engine {


	// Forward declare message handler from imgui_impl_win32.cpp
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	Win32Window::Win32Window(const std::string& name, int width, int height)
	{
		m_Name = name;
		m_Width = width;
		m_Height = height;


		ImGui_ImplWin32_EnableDpiAwareness();

		// Create application window
		wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "ImGui Example", NULL };
		RegisterClassEx(&wc);
		hwnd = CreateWindow(wc.lpszClassName, name.c_str(), WS_OVERLAPPEDWINDOW, 100, 100, width, height, NULL, NULL, wc.hInstance, NULL);
	}

	Win32Window::~Win32Window()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		DestroyWindow(hwnd);
		UnregisterClass(wc.lpszClassName, wc.hInstance);
	}


	void Win32Window::Update()
	{
		MSG msg;
		
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				shouldClose = true;
		}
		
	}

	bool Win32Window::ShouldClose()
	{
		return shouldClose;
	}

	void Win32Window::GetFrameBufferSize(int* width, int* height)
	{

	}

	
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

	// Win32 message handler
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_KEYDOWN:
			
			break;
		case WM_KEYUP:
			break;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_MOUSEWHEEL:
			GET_WHEEL_DELTA_WPARAM(wParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_DPICHANGED:
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
			{
				//const int dpi = HIWORD(wParam);
				//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
				const RECT* suggested_rect = (RECT*)lParam;
				::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
			}
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}


}