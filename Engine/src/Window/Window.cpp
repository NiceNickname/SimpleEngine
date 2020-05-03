#include "Window.h"
#include <iostream>
Window::Window()
{
	Init();
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Init()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
		std::cout << "glew not initialized" << std::endl;

	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);

}

void Window::Update()
{
	glfwSwapBuffers(m_Window);

	/* Poll for and process events */
	glfwPollEvents();
}
