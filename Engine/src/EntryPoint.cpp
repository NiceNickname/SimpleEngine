#include <stdlib.h>
#include <crtdbg.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexBufferLayout.h"

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "glew not initialized" << std::endl;

	glEnable(GL_DEPTH_TEST);


	

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexBuffer* vertexbuffer = new VertexBuffer(vertices, sizeof(vertices));
	IndexBuffer* indexbuffer = new IndexBuffer(indices, sizeof(indices));
	VertexBufferLayout layout = { {"positions", DATATYPE::FLOAT3 },
									{"texCoord", DATATYPE::FLOAT2} };
	vertexbuffer->SetLayout(layout);
	VertexArray* arr = new VertexArray();
	arr->SetVB(vertexbuffer);
	arr->SetIB(indexbuffer);
	

	


	Shader* shader = new Shader("res/shaders/shader.vert", "res/shaders/shader.fragm");
	shader->Bind();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		arr->Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	shader->Unbind();

	delete shader;
	delete vertexbuffer;
	delete indexbuffer;
	delete arr;

	
	glfwTerminate();

	
	return 0;
}