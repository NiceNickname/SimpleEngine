#pragma once
#include <Gl/glew.h>
#include <GLFW/glfw3.h>



namespace Engine
{
	class Window
	{
	public:
		Window();
		~Window();
		void Init();
		void Update();
		inline GLFWwindow* GetPointer() { return m_Window; }

	private:
		GLFWwindow* m_Window;
		bool m_ShowDemo = true;
		
		
	};
}