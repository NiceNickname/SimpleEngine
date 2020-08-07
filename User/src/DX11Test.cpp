#include "Engine.h"

class DX11Game : public Engine::App
{
public:
	std::shared_ptr<Engine::VertexBuffer> m_VB;
	std::shared_ptr<Engine::IndexBuffer> m_IB;
	std::shared_ptr<Engine::Shader> m_Shader;

	bool ShowDemo = true;

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
			2, 3, 0
		};

		m_Shader.reset(Engine::Shader::Create("res/shaders/VertexShader.cso", "res/shaders/PixelShader.cso"));
		Engine::VertexBufferLayout layout = { {"POSITION", Engine::DATATYPE::FLOAT3 } };

		m_VB.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VB->SetShader(m_Shader);
		m_VB->SetLayout(layout);
		m_IB.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)));

		m_Shader->Bind();
		m_VB->Bind();
		m_IB->Bind();

	}

	void Update() override
	{

	}

	void Render() override
	{
		Engine::Renderer::DrawQuad(m_IB->GetCount());
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Hello world!");
		ImGui::Text("huita");
		ImGui::End();
	}
	~DX11Game()
	{
		Engine::Renderer::ShutDown();
	}

};

Engine::App* CreateApp()
{
	return new DX11Game();
}


