#include "Engine.h"

class DX11Game : public Engine::App
{
public:
	std::shared_ptr<Engine::VertexBuffer> m_VB;
	std::shared_ptr<Engine::IndexBuffer> m_IB;
	std::shared_ptr<Engine::Shader> m_Shader;

	glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };

	void Start() override
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			 0.5f, 0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 1
		};

		m_Shader.reset(Engine::Shader::Create("Shaders.shader", "Shaders.shader"));
		Engine::VertexBufferLayout layout = { {"POSITION", Engine::DATATYPE::FLOAT3 } };

		m_VB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IB.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)));


	}

	void Update() override
	{

	}

	void Render() override
	{
		Engine::Renderer::DrawQuad({0.0f, 0.0f, 0.0f}, m_IB->GetCount());
	}

	void ImGuiRender() override
	{

	}
	~DX11Game()
	{
		Engine::Renderer::ShutDown();
	}

};



