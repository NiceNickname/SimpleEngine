#pragma once


namespace Engine {


	class Window
	{

	public:

	enum class Type { WIN32WINDOW, GLFW };

		static Window* Create(Type type);

		virtual void Update() = 0;
		virtual bool ShouldClose() = 0;
		virtual void GetFrameBufferSize(int* width, int* height) = 0;
	};

}