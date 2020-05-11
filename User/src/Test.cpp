#include <Engine.h>
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/Renderer.h"

#include "EntryPoint.h"

class Game : public Engine::App
{
public:
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::Shader> m_BatchShader;
	std::shared_ptr<Engine::Texture> m_Texture;
	std::shared_ptr<Engine::OrthographicCamera> m_Camera;
	glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };

	virtual void Start() override
	{
		float vertices[] = {
			-10.f,  -10.0f,  0.0f, 0.0f, 0.0f,
			-10.0f,  -5.0f,  0.0f, 0.0f, 1.0f,
			 -5.0f,   -5.0f,  0.0f, 1.0f, 1.0f,
			 -5.0f,  -10.0f,  0.0f, 1.0f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		auto vertexbuffer = std::make_shared<Engine::VertexBuffer>(vertices, sizeof(vertices));
		auto indexbuffer = std::make_shared<Engine::IndexBuffer>(indices, sizeof(indices));

		m_Camera = std::make_shared<Engine::OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		m_Camera->SetPosition(CameraPosition);

		Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3 },
											  {"texCoord", Engine::DATATYPE::FLOAT2} };

		vertexbuffer->SetLayout(layout);

		m_VAO = std::make_shared<Engine::VertexArray>();
		m_VAO->SetVB(vertexbuffer);
		m_VAO->SetIB(indexbuffer);

		m_Shader = std::make_shared<Engine::Shader>("res/shaders/shader.vert", "res/shaders/shader.fragm");
		m_Shader->Bind();
		m_Shader->SetUniform1i("tex", 1);
		m_Shader->SetUniformMat4f("view", m_Camera->GetView());

		m_Texture = std::make_shared<Engine::Texture>("res/textures/checkerboard.jpg");

		m_BatchShader = std::make_shared<Engine::Shader>("res/shaders/BatchShader.vert", "res/shaders/BatchShader.fragm");
		m_BatchShader->Bind();
		m_BatchShader->SetUniformMat4f("view", m_Camera->GetView());


		int samplers[10];
		for (int i = 0; i < 10; i++)
			samplers[i] = i;
		m_BatchShader->SetUniformIntArray("u_Textures", sizeof(samplers), samplers);


		Engine::Renderer::Init();

	}

	void Update() override
	{
		m_Camera->SetPosition(CameraPosition);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("view", m_Camera->GetView());

		m_BatchShader->Bind();
		m_BatchShader->SetUniformMat4f("view", m_Camera->GetView());

		if (Engine::Input::IsKeyDown(GLFW_KEY_SPACE))
			std::cout << "Space pressed" << std::endl;


		
	}

	void Render() override
	{
		m_BatchShader->Bind();

		Engine::Renderer::Begin();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
				Engine::Renderer::DrawQuad({ j, i, 0.0f }, { 1.0f, 1.0f }, color);
				Engine::Renderer::DrawQuad({ j + 5, i, 0.0f }, { 1.0f, 1.0f}, m_Texture);
			}
		}

		Engine::Renderer::End();

		Engine::Renderer::Draw();

		m_Shader->Bind();
		m_Texture->Bind(1);
		m_VAO->Bind();
		m_VAO->Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Hello, World!");
		ImGui::SliderFloat3("Camera Position", &CameraPosition.x, -10.0f, 10.0f);
		ImGui::End();
	}

	~Game()
	{
		Engine::Renderer::ShutDown();
	}
};

Engine::App* CreateApp()
{
	return new Game();
}