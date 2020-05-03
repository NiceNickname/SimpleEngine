#include <Engine.h>

class Game : public App
{
	virtual void Run() override
	{
		m_Window = new Window();


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
		shader->SetUniform1i("tex", 0);

		Texture* texture = new Texture("res/textures/checkerboard.jpg");
		texture->Bind();

		/* Loop until the user closes the window */
		while (m_Running)
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			arr->Draw();

			m_Window->Update();
		}
		shader->Unbind();

		delete shader;
		delete vertexbuffer;
		delete indexbuffer;
		delete arr;
	}
};

App* CreateApp()
{
	return new Game();
}