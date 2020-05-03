#pragma once
#include <Gl/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();
	void Init();
	void Update();

private:
	GLFWwindow* m_Window;
	
};