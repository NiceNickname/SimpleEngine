#include "Engine.h"
#include <Windows.h>

#define TEST 0

class DX11Game : public Engine::App
{
public:
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::OrthographicCamera> m_Camera;
	std::shared_ptr<Engine::Texture> m_Texture;

	glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };
	

	void ChooseApi() override
	{
		m_Api = Engine::Renderer2D::API::DX11;
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


		m_Texture.reset(Engine::Texture::Create("res/textures/checkerboard.jpg"));
		m_Texture->Bind(1);

		m_Camera = std::make_shared<Engine::OrthographicCamera>(16.0f / 9.0f);
		m_Camera->SetPosition(CameraPosition);


		m_Shader.reset(Engine::Shader::Create("res/shaders/VertexShader.cso", "res/shaders/PixelShader.cso"));
		m_Shader->Bind();

		Engine::UniformElement layout[] = { {"view", Engine::DATATYPE::MAT4}  };

		m_Shader->SetUniformLayout(layout, sizeof(layout) / sizeof(Engine::UniformElement));

		// TODO: move this to app class
		Engine::Renderer2D::Init();

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
		Engine::Renderer2D::Begin();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
				Engine::Renderer2D::DrawQuad({ j, i, 0.0f }, { 0.8f, 0.8f }, color);
				Engine::Renderer2D::DrawQuad({ j + 5, i, 0.0f }, { 0.8f, 0.8f }, m_Texture);
			}
		}

		Engine::Renderer2D::End();

		Engine::Renderer2D::Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Render stats");
		ImGui::Text("Draw Calls: %d", Engine::Renderer2D::GetStats().DrawCallsCount);
		ImGui::Text("Quads Count: %d", Engine::Renderer2D::GetStats().QuadsCount);
		ImGui::Text("Quads Per Draw Call: %d", Engine::Renderer2D::GetStats().QuadPerDrawCall);
		ImGui::End();
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


