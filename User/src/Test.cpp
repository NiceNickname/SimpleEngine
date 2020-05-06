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

		auto vertexbuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
		auto indexbuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices));


		VertexBufferLayout layout = { {"positions", DATATYPE::FLOAT3 },
										{"texCoord", DATATYPE::FLOAT2} };

		vertexbuffer->SetLayout(layout);

		auto arr = std::make_shared<VertexArray>();
		arr->SetVB(vertexbuffer);
		arr->SetIB(indexbuffer);

		
		Vector3f position(0.5f, 0.5f, 0.0f);
		Mat4f model = Mat4f::Translate(position);

		auto shader = std::make_shared<Shader>("res/shaders/shader.vert", "res/shaders/shader.fragm");
		shader->Bind();
		shader->SetUniform1i("tex", 0);
		shader->SetUniformMat4f("model", model);

		auto texture = std::make_shared<Texture>("res/textures/checkerboard.jpg");
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