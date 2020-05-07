#include <Engine.h>

class Game : public Engine::App
{
	virtual void Run() override
	{
		m_Window = std::make_unique<Engine::Window>();


		float vertices[] = {
			-0.5f,  -0.5f,  0.0f, 0.0f, 0.0f,
			-0.5f,   0.5f,  0.0f, 0.0f, 1.0f,
			 0.5f,   0.5f,  0.0f, 1.0f, 1.0f,
			 0.5f,  -0.5f,  0.0f, 1.0f, 0.0f,

			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			-0.75f, -0.25f, 0.0f, 0.0f, 1.0f,
			-0.25f, -0.25f, 0.0f, 1.0f, 1.0f,
			-0.25f, -0.75f, 0.0f, 1.0f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		auto vertexbuffer = std::make_shared<Engine::VertexBuffer>(vertices, sizeof(vertices));
		auto indexbuffer = std::make_shared<Engine::IndexBuffer>(indices, sizeof(indices));


		Engine::Mat4f view = Engine::Mat4f::Translate({-0.5f, -0.5f, 0.0f});

		Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3 },
											  {"texCoord", Engine::DATATYPE::FLOAT2} };

		vertexbuffer->SetLayout(layout);

		auto arr = std::make_shared<Engine::VertexArray>();
		arr->SetVB(vertexbuffer);
		arr->SetIB(indexbuffer);

		auto shader = std::make_shared<Engine::Shader>("res/shaders/shader.vert", "res/shaders/shader.fragm");
		shader->Bind();
		shader->SetUniform1i("tex", 1);
		shader->SetUniformMat4f("view", view);

		auto texture = std::make_shared<Engine::Texture>("res/textures/checkerboard.jpg");
		texture->Bind(1);

		/* Loop until the user closes the window */
		while (m_Running)
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Update();

			arr->Draw();

			m_Window->Update();
		}
	}

	void Update()
	{
		if (Engine::Input::IsKeyDown(GLFW_KEY_SPACE))
			std::cout << "Space pressed" << std::endl;
	}
};

Engine::App* CreateApp()
{
	return new Game();
}