#include <Engine.h>

class Game : public Engine::App
{
public:
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::Texture> m_Texture;

	virtual void Start() override
	{
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

		m_VAO = std::make_shared<Engine::VertexArray>();
		m_VAO->SetVB(vertexbuffer);
		m_VAO->SetIB(indexbuffer);

		m_Shader = std::make_shared<Engine::Shader>("res/shaders/shader.vert", "res/shaders/shader.fragm");
		m_Shader->Bind();
		m_Shader->SetUniform1i("tex", 1);
		m_Shader->SetUniformMat4f("view", view);

		m_Texture = std::make_shared<Engine::Texture>("res/textures/checkerboard.jpg");
		m_Texture->Bind(1);

	}

	void Update() override
	{
		if (Engine::Input::IsKeyDown(GLFW_KEY_SPACE))
			std::cout << "Space pressed" << std::endl;
	}

	void Render() override
	{
		m_VAO->Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Hello, World!");
		ImGui::End();
	}
};

Engine::App* CreateApp()
{
	return new Game();
}