#include "Engine.h"

#define TEST 1

class DX11Game : public Engine::App
{
public:
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::OrthographicCamera> m_Camera;

	glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };
	
	bool ShowDemo = true;

	void ChooseApi() override
	{
		m_Api = Engine::Renderer::API::DX11;
	}
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


		Engine::VertexBufferLayout layout = { {"POSITION", Engine::DATATYPE::FLOAT3 }, {"COLOR", Engine::DATATYPE::FLOAT4} };

		m_Camera = std::make_shared<Engine::OrthographicCamera>(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		m_Camera->SetPosition(CameraPosition);


		m_Shader.reset(Engine::Shader::Create("res/shaders/VertexShader.cso", "res/shaders/PixelShader.cso"));
		m_Shader->Bind();

		// TODO: move this to app class
		Engine::Renderer::Init();

	}

	void Update() override
	{
		m_Shader->SetUniformMat4f("view", m_Camera->GetView());
	}

	void Render() override
	{
		Engine::Renderer::Begin();
		Engine::Renderer::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f});
		Engine::Renderer::End();

		Engine::Renderer::Draw();
	}

	void ImGuiRender() override
	{
		if (ShowDemo)
			ImGui::ShowDemoWindow(&ShowDemo);
	}
	
	~DX11Game()
	{
	}

};

#if TEST
Engine::App* CreateApp()
{
	return new DX11Game();
}
#endif


