#include <Engine.h>

#include "EntryPoint.h"

class Game : public Engine::App
{
public:
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::Shader> m_BatchShader;
	std::shared_ptr<Engine::OpenGLTexture> m_Texture;
	std::shared_ptr<Engine::OrthographicCamera> m_Camera;

	glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };

	virtual void Start() override
	{
		float vertices[] = {
			-10.0f, -10.0f, 0.0f, 0.0f, 0.0f,
			-10.0f,  -5.0f, 0.0f, 0.0f, 1.0f,
			 -5.0f,  -5.0f, 0.0f, 1.0f, 1.0f,
			 -5.0f, -10.0f, 0.0f, 1.0f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<Engine::VertexBuffer> vertexbuffer;
		vertexbuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		
		std::shared_ptr<Engine::IndexBuffer> indexbuffer;
		indexbuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)));

		m_Camera = std::make_shared<Engine::OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		m_Camera->SetPosition(CameraPosition);

		Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3 },
											  {"texCoord", Engine::DATATYPE::FLOAT2} };

		vertexbuffer->SetLayout(layout);

		m_VAO = std::make_shared<Engine::VertexArray>();
		m_VAO->SetVB(vertexbuffer);
		m_VAO->SetIB(indexbuffer);

		m_Shader.reset(Engine::Shader::Create("res/shaders/shader.vert", "res/shaders/shader.fragm"));
		//m_Shader = std::make_shared<Engine::OpenGLShader>("res/shaders/shader.vert", "res/shaders/shader.fragm");
		m_Shader->Bind();
		m_Shader->SetUniform1i("tex", 1);
		m_Shader->SetUniformMat4f("view", m_Camera->GetView());

		m_Texture = std::make_shared<Engine::OpenGLTexture>("res/textures/checkerboard.jpg");

		m_BatchShader = std::make_shared<Engine::OpenGLShader>("res/shaders/BatchShader.vert", "res/shaders/BatchShader.fragm");
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
		if (Engine::Input::IsKeyDown(GLFW_KEY_RIGHT))
			CameraPosition.x += 0.01f;
		if (Engine::Input::IsKeyDown(GLFW_KEY_LEFT))
			CameraPosition.x -= 0.01f;
		if (Engine::Input::IsKeyDown(GLFW_KEY_UP))
			CameraPosition.y += 0.01f;
		if (Engine::Input::IsKeyDown(GLFW_KEY_DOWN))
			CameraPosition.y -= 0.01f;

		if (Engine::Input::IsKeyDown(GLFW_KEY_SPACE))
			Engine::Renderer::SetApi(Engine::Renderer::API::OPENGL, GetWindowPtr());

		m_Camera->SetPosition(CameraPosition);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("view", m_Camera->GetView());

		m_BatchShader->Bind();
		m_BatchShader->SetUniformMat4f("view", m_Camera->GetView());
		
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
				Engine::Renderer::DrawQuad({ j, i, 0.0f }, { 0.8f, 0.8f }, color);
				Engine::Renderer::DrawQuad({ j + 5, i, 0.0f }, { 0.8f, 0.8f}, m_Texture);
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