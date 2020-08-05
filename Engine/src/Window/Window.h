#pragma once


namespace Engine {

	enum class WindowType
	{
		WIN32 = 0, GLFW
	};

	class Window
	{
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;

		static Window* Create(WindowType type);

		virtual bool ShouldClose() = 0;
		virtual void GetFrameBufferSize(int* width, int* height) = 0;
	};

}