#include "Engine.h"
#include <Windows.h>

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

		m_Camera = std::make_shared<Engine::OrthographicCamera>(16.0f / 9.0f);
		m_Camera->SetPosition(CameraPosition);


		m_Shader.reset(Engine::Shader::Create("res/shaders/VertexShader.cso", "res/shaders/PixelShader.cso"));
		m_Shader->Bind();

		// TODO: move this to app class
		Engine::Renderer::Init();

	}

	void Update() override
	{
		if (Engine::Input::IsKeyDown(VK_RIGHT))
			CameraPosition.x += m_Camera->GetSpeed();
		if (Engine::Input::IsKeyDown(VK_LEFT))
			CameraPosition.x -= m_Camera->GetSpeed();
		if (Engine::Input::IsKeyDown(VK_UP))
			CameraPosition.y += m_Camera->GetSpeed();
		if (Engine::Input::IsKeyDown(VK_DOWN))
			CameraPosition.y -= m_Camera->GetSpeed();

		m_Camera->SetPosition(CameraPosition);
		m_Camera->Zoom(Engine::Input::GetMouseWheelOffset());
		m_Shader->SetUniformMat4f("view", m_Camera->GetProjection() * m_Camera->GetView());
	}

	void Render() override
	{
		Engine::Renderer::Begin();
		for (float x = 0.0f; x < 11.0f; x += 0.55f)
		{
			for (float y = 0.0f; y < 11.0f; y += 0.55f)
			{
				Engine::Renderer::DrawQuad({ x, y, 0.0f }, { 0.5f, 0.5f }, {1.0f, 0.0f, 0.0f, 1.0f});
			}
		}
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


