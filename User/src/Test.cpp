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

		
		Vector3f position(0.5f, 0.5f, 0.0f);
		Mat4f model = Mat4f::Translate(position);

		Shader* shader = new Shader("res/shaders/shader.vert", "res/shaders/shader.fragm");
		shader->Bind();
		shader->SetUniform1i("tex", 0);
		shader->SetUniformMat4f("model", model);

		Texture* texture = new Texture("res/textures/checkerboard.jpg");
		texture->Bind();

		/* Loop until the user closes the window */
		while (m_Running)
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Update();

			arr->Draw();

			m_Window->Update();
		}
		shader->Unbind();

		delete shader;
		delete vertexbuffer;
		delete indexbuffer;
		delete arr;

	}

	void Update()
	{
		if (Input::IsKeyDown(GLFW_KEY_SPACE))
			std::cout << "Space pressed" << std::endl;
	}
};

App* CreateApp()
{
	return new Game();
}